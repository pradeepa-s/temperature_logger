/*
 * response_generator.c
 *
 *  Created on: Aug 18, 2023
 *      Author: prade
 */

#include "response_generator.h"
#include "tmp112.h"
#include "datetime.h"
#include "storage_manager.h"
#include "command_defs.h"
#include <string.h>

#define RESPONSE_DESIGNATOR (0x02)
#define GET_STATUS_RESPONSE_SIZE (14)
#define SET_DATETIME_PARAM_LENGTH (6)
static uint8_t response[GET_STATUS_RESPONSE_SIZE] = {};
static uint8_t is_response_ready = 0;
static uint8_t response_length = 0;

static void generate_response_without_data(const uint8_t response_code, const uint8_t error_code);
static void generate_response(const uint8_t response_code, const uint8_t error_code, const uint8_t *data, const uint16_t data_length);

uint8_t rg_is_response_ready()
{
	return is_response_ready;
}

uint16_t rg_read_response(uint8_t *buffer, const size_t length)
{
	if (buffer && length >= response_length && is_response_ready)
	{
		memcpy(buffer, response, response_length);
		is_response_ready = 0;
		uint8_t response_length_copy = response_length;
		response_length = 0;
		return response_length_copy;
	}
	return 0;
}

void rg_generate_get_status_response()
{
	const datetime dt = get_datetime();
	const int temperature = tmp112_read_temperature();

	uint8_t data[10] = {dt.year, dt.month, dt.date, dt.hour, dt.minute, dt.second};
	memcpy(&data[6], &temperature, sizeof(temperature));

	generate_response(GET_STATUS_CMD, NO_ERROR, data, sizeof(data));
}

void rg_process_set_datetime_cmd(const uint8_t* buffer, const uint16_t length)
{
	int is_success = -1;

	if (length == SET_DATETIME_PARAM_LENGTH)
	{
		// yy - mm - dd - hh - mm - ss
		datetime dt = {
				.year=buffer[0], .month=buffer[1], .date=buffer[2],
				.hour=buffer[3], .minute=buffer[4], .second=buffer[5]};
		is_success  = set_datetime(dt);
	}

	if (is_success == 0)
	{
		const datetime dt = get_datetime();

		uint8_t data[] = {dt.year, dt.month, dt.date, dt.hour, dt.minute, dt.second};
		generate_response(SET_DATETIME_CMD, NO_ERROR, data, sizeof(data));
	}
	else
	{
		// Invalid parameters error
		generate_response_without_data(SET_DATETIME_CMD, INVALID_PARAMETERS);
	}
}

void rg_generate_chip_erase_response()
{
	sm_chip_erase();

	generate_response_without_data(CHIP_ERASE_CMD, NO_ERROR);
}

void generate_response_without_data(const uint8_t response_code, const uint8_t error_code)
{
	uint8_t data[] = {0x00, 0x00};
	generate_response(response_code, error_code, data, sizeof(data));
}

void generate_response(const uint8_t response_code, const uint8_t error_code, const uint8_t *data, const uint16_t data_length)
{
	response[0] = RESPONSE_DESIGNATOR;
	response[1] = response_code;
	response[2] = error_code;

	memcpy(&response[3], &data_length, sizeof(data_length));
	memcpy(&response[5], data, data_length);

	is_response_ready = 1;

	// There are five mandatory fields in any response
	response_length = 5 + data_length;
}
