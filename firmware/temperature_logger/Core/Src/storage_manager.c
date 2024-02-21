/*
 * storage_manager.c
 *
 *  Created on: Jan 27, 2024
 *      Author: prade
 */

#include "storage_manager.h"
#include "spi.h"
#include "gpio.h"

#define DEFAULT_TIMEOUT  (0xFFFFFFFF)

typedef struct STATUS_REG_READING
{
	HAL_StatusTypeDef status;
	uint8_t value;
} STATUS_REG_READING;

static void write_enable();
static void send_chip_erase_command();
static void wait_for_operation();
static STATUS_REG_READING read_status_reg();
static void chip_select();
static void chip_deselect();

void sm_chip_erase()
{
	// Write enable
	write_enable();

	// Chip erase
	send_chip_erase_command();

	// Wait until done
	wait_for_operation();
}

void write_enable()
{
	chip_select();

	uint8_t write_enable_command[] = {0x06};

	HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi2, write_enable_command,
			sizeof(write_enable_command), DEFAULT_TIMEOUT);

	chip_deselect();

	if (status == HAL_OK)
	{
		// Wait until write enable is complete
		while (1)
		{
			STATUS_REG_READING status_reading = read_status_reg();

			if ((status_reading.status == HAL_OK && (status_reading.value & 0x02)) || (status_reading.status != HAL_OK))
			{
				break;
			}
		}
	}
}

void send_chip_erase_command()
{
	chip_select();

	uint8_t chip_erase_command[] = {0x60};
	HAL_SPI_Transmit(&hspi2, chip_erase_command, sizeof(chip_erase_command), DEFAULT_TIMEOUT);

	chip_deselect();
}

void wait_for_operation()
{
	while (1)
	{
		chip_select();

		STATUS_REG_READING status_reading = read_status_reg();
		chip_deselect();

		if (status_reading.status == HAL_OK && (status_reading.value & 0x01) == 0x00)
		{
			break;
		}
	}
}

STATUS_REG_READING read_status_reg()
{
	STATUS_REG_READING reading;

	uint8_t rdsr_command[] = {0x05};

	chip_select();
	reading.status = HAL_SPI_Transmit(&hspi2, rdsr_command,
			sizeof(rdsr_command), DEFAULT_TIMEOUT);

	if (reading.status == HAL_OK)
	{
		reading.status = HAL_SPI_Receive(&hspi2, &reading.value, sizeof(reading.value), DEFAULT_TIMEOUT);
	}

	chip_deselect();

	return reading;
}

void chip_select()
{
	HAL_GPIO_WritePin(FLASH_NCS_GPIO_Port, FLASH_NCS_Pin, GPIO_PIN_RESET);
}

void chip_deselect()
{
	HAL_GPIO_WritePin(FLASH_NCS_GPIO_Port, FLASH_NCS_Pin, GPIO_PIN_SET);
}
