/*
 * tmp112.c
 *
 *  Created on: Jul 18, 2023
 *      Author: prade
 */

#include <stdint.h>
#include "tmp112.h"
#include "i2c.h"

int tmp112_read_temperature()
{
	uint8_t register_address[1] = {0x00};
	uint8_t temperature_reading[2] = {0x00, 0x00};

	HAL_I2C_Master_Transmit(&hi2c1, 0x48 << 1, register_address,sizeof(register_address), 0xFFFFFFFF);
	HAL_I2C_Master_Receive(&hi2c1, 0x48 << 1, temperature_reading, sizeof(temperature_reading), 0xFFFFFFFF);

	uint16_t raw_reading = (((temperature_reading[0] << 8) | temperature_reading[1]) >> 4);

	// To avoid floating point calculations:
	// 0.0625 * 10000 = 625
	const int temperature_c = raw_reading * 625;

	return temperature_c;
}
