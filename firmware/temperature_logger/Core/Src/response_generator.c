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

	response[0] = 0x02;
	response[1] = 0x00;
	response[2] = 0x0A;
	response[3] = 0x00;
	response[4] = dt.year;
	response[5] = dt.month;
	response[6] = dt.date;
	response[7] = dt.hour;
	response[8] = dt.minute;
	response[9] = dt.second;
	memcpy(&response[10], &temperature, sizeof(temperature));

	is_response_ready = 1;
	response_length = 14;
}
