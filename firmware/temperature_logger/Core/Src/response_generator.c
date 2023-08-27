/*
 * response_generator.c
 *
 *  Created on: Aug 18, 2023
 *      Author: prade
 */

#include "response_generator.h"
#include "tmp112.h"
#include "datetime.h"
#include <string.h>

#define GET_STATUS_RESPONSE_SIZE (14)
#define SET_DATETIME_PARAM_LENGTH (6)
static uint8_t response[GET_STATUS_RESPONSE_SIZE] = {};
static uint8_t is_response_ready = 0;
static uint8_t response_length = 0;

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

	response[0] = 0x02;  // Response
	response[1] = 0x00;  // GetStatus
	response[2] = 0x00;  // No Error
	response[3] = 0x0A;  // Length
	response[4] = 0x00;  // Length
	response[5] = dt.year;
	response[6] = dt.month;
	response[7] = dt.date;
	response[8] = dt.hour;
	response[9] = dt.minute;
	response[10] = dt.second;
	memcpy(&response[11], &temperature, sizeof(temperature));

	is_response_ready = 1;
	response_length = 15;
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

		response[0] = 0x02;   // Response
		response[1] = 0x01;   // SetDatetime function
		response[2] = 0x00;   // No error
		response[3] = 0x06;   // Length
		response[4] = 0x00;   // Length
		response[5] = dt.year;
		response[6] = dt.month;
		response[7] = dt.date;
		response[8] = dt.hour;
		response[9] = dt.minute;
		response[10] = dt.second;

		is_response_ready = 1;
		response_length = 11;
	}
	else
	{
		response[0] = 0x02;   // Response
		response[1] = 0x01;   // SetDatetime function
		response[2] = 0x01;   // Invalid parameters error
		response[3] = 0x00;   // Length
		response[4] = 0x00;   // Length

		is_response_ready = 1;
		response_length = 5;
	}
}
