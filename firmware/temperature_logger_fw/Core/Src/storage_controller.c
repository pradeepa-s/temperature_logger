/*
 * storage_controller.c
 *
 *  Created on: 18 Nov. 2022
 *      Author: Pradeepa
 */

#include "storage_controller.h"
#include "spi.h"
#include <string.h>
#include "rtc.h"

#define BACKUP_REG_NEXT_WRITE_ADDRESS (0)

static unsigned int g_write_address = 0;
static unsigned int g_read_address = 0;

static void _write_to_flash_blocking(unsigned int write_address, const char *data, const size_t size);
static void _read_from_flash_blocking(unsigned int read_address, char *out_buffer, unsigned short read_size);
static void _wait_for_write();
static void _spi_flash_cs_high();
static void _spi_flash_cs_low();
static void _write_enable();

void storage_controller_init()
{
	// The options to keep track of the write address:
	//		1. Backup registers
	//			Pros:
	//				- Infinite erase/write cycles
	//				- Fast
	//			Cons:
	//				- Volatile
	//
	//		2. EEPROM
	//			Pros:
	//				- Non volatile
	//			Cons:
	//				- Finite erase-write cycles
	//				- Slow
	//
	// Both these memories would retaing their data in low power modes.
	//
	// Since this is a battery powered device and there is no proper
	// way to recover from losing battery power, it's better to use
	// the fast and more durable memory, which is the backup registers.
	g_write_address = HAL_RTCEx_BKUPRead(&hrtc, BACKUP_REG_NEXT_WRITE_ADDRESS);

	if (g_write_address == 0)
	{
		uint32_t out = 0;
		uint32_t read_address = 0;
		const uint32_t sector_size = 0x1000;
		uint32_t last_write_sector = 0;

		// Find last sector
		for (last_write_sector = 0; last_write_sector < 512; ++last_write_sector, out = 0, read_address += sector_size)
		{
			_read_from_flash_blocking(read_address, (char *)&out, sizeof(out));

			if (out == 0xffffffff)
			{
				if (last_write_sector)
				{
					--last_write_sector;
				}
				break;
			}
		}

		uint32_t start_of_last_sector = last_write_sector * sector_size;
		uint32_t start_of_entry_in_sector =  start_of_last_sector % sizeof(storage_entry);

		if (start_of_entry_in_sector != 0)
		{
			start_of_entry_in_sector = sizeof(storage_entry) - start_of_entry_in_sector;
		}

		uint32_t start_of_reading = start_of_last_sector + start_of_entry_in_sector;

		g_write_address = start_of_reading;

		out = 0;
		_read_from_flash_blocking(g_write_address, (char *)&out, sizeof(out));
		while (out != 0xffffffff)
		{
			g_write_address += sizeof(storage_entry);
			_read_from_flash_blocking(g_write_address, (char *)&out, sizeof(out));
		}
	}
}

storage_status flash_storage_erase_full()
{
	_write_enable();

	uint8_t erase = 0x60;

	_spi_flash_cs_low();
	HAL_SPI_Transmit(&hspi2, &erase, sizeof(erase), 0xFFFFFFFF);
	_spi_flash_cs_high();

	_wait_for_write();

	g_write_address = 0;
	HAL_RTCEx_BKUPWrite(&hrtc, BACKUP_REG_NEXT_WRITE_ADDRESS, g_write_address);

	return storge_status_OK;
}

storage_status flash_storage_write(storage_entry *entries, uint8_t count)
{
	for (int i = 0; i < count; i++)
	{
		const storage_entry *entry = &entries[i];

		_write_to_flash_blocking(g_write_address, (const char*)entry, sizeof(storage_entry));

		g_write_address += sizeof(storage_entry);
		HAL_RTCEx_BKUPWrite(&hrtc, BACKUP_REG_NEXT_WRITE_ADDRESS, g_write_address);
	}

	return storge_status_OK;
}

void flash_storage_read_start()
{
	g_read_address = 0;
}

unsigned int flash_storage_read(storage_entry *entries, uint8_t count)
{
	int i = 0;
	for (i = 0; i < count; i++)
	{
		_read_from_flash_blocking(g_read_address, (char*)(&entries[i]), sizeof(storage_entry));

		// Check whether the entry is valid
		char empty_flash[sizeof(storage_entry)] = {0};
		memset(empty_flash, 0xff, sizeof(storage_entry));
		if (0 == memcmp(empty_flash, &entries[i], sizeof(storage_entry)))
		{
			break;
		}
		else
		{
			g_read_address += sizeof(storage_entry);
		}
	}

	return i;
}

void _read_from_flash_blocking(unsigned int read_address, char *out_buffer, unsigned short read_size)
{
	uint8_t read_command[4];

	read_command[0] = 0x03;
	read_command[1] = (read_address & 0x00FF0000) >> 16;
	read_command[2] = (read_address & 0x0000FF00) >> 8;
	read_command[3] = (read_address & 0x000000FF);

	_spi_flash_cs_low();
	HAL_SPI_Transmit(&hspi2, read_command, sizeof(read_command), 0xFFFFFFFF);
	HAL_SPI_Receive(&hspi2, (uint8_t*)out_buffer, read_size, 0xFFFFFFFF);
	_spi_flash_cs_high();
}

void _write_to_flash_blocking(unsigned int write_address, const char *data, const size_t size)
{
	_write_enable();

	// Write data
	uint8_t page_program[50];
	memset(page_program, 0x00, 50);

	unsigned int page_boundary = 256 - (write_address % 256);

	page_program[0] = 0x02;
	page_program[1] = (write_address & 0x00FF0000) >> 16;
	page_program[2] = (write_address & 0x0000FF00) >> 8;
	page_program[3] = (write_address & 0x000000FF);

	if (page_boundary >= size)
	{
		memcpy(&page_program[4], data, size);

		_spi_flash_cs_low();
		HAL_SPI_Transmit(&hspi2, page_program, size + 4, 0xFFFFFFFF);
		_spi_flash_cs_high();

		_wait_for_write();
	}
	else
	{
		memcpy(&page_program[4], data, page_boundary);

		_spi_flash_cs_low();
		HAL_SPI_Transmit(&hspi2, page_program, page_boundary + 4, 0xFFFFFFFF);
		_spi_flash_cs_high();

		_wait_for_write();

		_write_enable();

		unsigned int next_address = write_address + page_boundary;
		page_program[1] = (next_address & 0x00FF0000) >> 16;
		page_program[2] = (next_address & 0x0000FF00) >> 8;
		page_program[3] = (next_address & 0x000000FF);

		memcpy(&page_program[4], &data[page_boundary], size - page_boundary);

		_spi_flash_cs_low();
		HAL_SPI_Transmit(&hspi2, page_program, size - page_boundary + 4, 0xFFFFFFFF);
		_spi_flash_cs_high();

		_wait_for_write();
	}

	write_address += size;
}

void _write_enable()
{
	// Send the write enable command
	_spi_flash_cs_low();
	uint8_t write_enable[] = {0x06};
	HAL_SPI_Transmit(&hspi2, write_enable, sizeof(write_enable), 0xFFFFFFFF);
	_spi_flash_cs_high();
}

void _wait_for_write()
{
	// Wait for write complete
	uint8_t status = 0x01;
	while(status & 0x01)
	{
		_spi_flash_cs_low();
		uint8_t read_status[] = {0x05};
		HAL_SPI_Transmit(&hspi2, read_status, sizeof(read_status), 0xFFFFFFFF);
		HAL_SPI_Receive(&hspi2, &status, sizeof(status), 0xFFFFFFFF);
		_spi_flash_cs_high();
	}
}

void _spi_flash_cs_low()
{
	HAL_GPIO_WritePin(SPI_CSN_GPIO_Port, SPI_CSN_Pin, GPIO_PIN_RESET);
}

void _spi_flash_cs_high()
{
	HAL_GPIO_WritePin(SPI_CSN_GPIO_Port, SPI_CSN_Pin, GPIO_PIN_SET);
}
