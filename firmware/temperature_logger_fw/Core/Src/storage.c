/*
 * storage.c
 *
 *  Created on: 15 Aug 2021
 *      Author: Pradeepa
 */

#include "storage.h"
#include "spi.h"
#include <string.h>

static storage_values temp_readings;

static uint32_t get_write_address();
static uint8_t write_to_flash(temperature_reading data, uint32_t address);
static void increment_last_modified_location();
static void _spi_flash_cs_low();
static void _spi_flash_cs_high();
static void write_enable();
static void wait_for_write();
static const storage_values* read_from_address(uint32_t read_address);

static uint32_t write_address = 0x0;
static uint32_t read_address = 0x0;

uint8_t storage_write(temperature_reading data)
{
	uint32_t next_address = get_write_address();

	write_to_flash(data, next_address);

	increment_last_modified_location();

	return 0;
}

uint8_t write_to_flash(temperature_reading data, uint32_t address)
{
	write_enable();

	// Write data
	uint32_t write_address = get_write_address();
	uint8_t page_program[12];

	page_program[0] = 0x02;
	page_program[1] = (write_address & 0x00FF0000) >> 16;
	page_program[2] = (write_address & 0x0000FF00) >> 8;
	page_program[3] = (write_address & 0x000000FF);
	memcpy(&page_program[4], &data, sizeof(data));

	_spi_flash_cs_low();
	HAL_SPI_Transmit(&hspi2, page_program, sizeof(page_program), 0xFFFFFFFF);
	_spi_flash_cs_high();

    wait_for_write();
	return 0;
}

const storage_values* storage_read(uint32_t datetime)
{
    return read_from_address(0);
}

const storage_values* read_from_address(uint32_t read_address)
{
	uint8_t read_command[4];

	read_command[0] = 0x03;
	read_command[1] = (read_address & 0x00FF0000) >> 16;
	read_command[2] = (read_address & 0x0000FF00) >> 8;
	read_command[3] = (read_address & 0x000000FF);

	_spi_flash_cs_low();
	HAL_SPI_Transmit(&hspi2, read_command, sizeof(read_command), 0xFFFFFFFF);
	HAL_SPI_Receive(&hspi2, (uint8_t*)temp_readings.readings, 10 * sizeof(temperature_reading), 0xFFFFFFFF);

    int read_count = 0;
    for (read_count = 0; read_count < _MAXIMUM_READ_COUNT; read_count++)
    {
        if (temp_readings.readings[read_count].datetime == 0xFFFFFFFF)
        {
            break;
        }
    }

	temp_readings.count = read_count;

	return &temp_readings;
}

void erase_first_sector()
{
	write_enable();

	uint32_t sector = 0;
	uint8_t sector_erase[4];

	sector_erase[0] = 0x20;
	sector_erase[1] = (sector & 0x00FF0000) >> 16;
	sector_erase[2] = (sector & 0x0000FF00) >> 8;
	sector_erase[3] = (sector & 0x000000FF);

	_spi_flash_cs_low();
	HAL_SPI_Transmit(&hspi2, sector_erase, sizeof(sector_erase), 0xFFFFFFFF);
	_spi_flash_cs_high();

	wait_for_write();
}

const storage_values* storage_read_start()
{
	read_address = 0x00;
    return storage_read_cont();
}

const storage_values* storage_read_cont()
{
    read_from_address(read_address);
    read_address += temp_readings.count * sizeof(temperature_reading);
    return &temp_readings;
}

uint32_t get_write_address()
{
	return write_address;
}

void increment_last_modified_location()
{
	write_address += sizeof(temperature_reading);
}

void write_enable()
{
	// Send the write enable command
	_spi_flash_cs_low();
	uint8_t write_enable[] = {0x06};
	HAL_SPI_Transmit(&hspi2, write_enable, sizeof(write_enable), 0xFFFFFFFF);
	_spi_flash_cs_high();

	// Wait for write enable
	uint8_t status = 0x00;
	while(0x00 == (status & 0x02))
	{
		_spi_flash_cs_low();
		uint8_t read_status[] = {0x05};
		HAL_SPI_Transmit(&hspi2, read_status, sizeof(read_status), 0xFFFFFFFF);
		HAL_SPI_Receive(&hspi2, &status, sizeof(status), 0xFFFFFFFF);
		_spi_flash_cs_high();
	}
}

void wait_for_write()
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
