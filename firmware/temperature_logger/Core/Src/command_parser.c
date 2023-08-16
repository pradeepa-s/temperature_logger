/*
 * command_parser.c
 *
 *  Created on: Aug 12, 2023
 *      Author: prade
 */

#include "command_parser.h"
#include "dbg_printf.h"
#include <string.h>

#define CMD_BUFFER_SIZE (10)
#define TLOG_COMMAND (0x01)
#define CMD_HEADER_SIZE (3)

#define GET_STATUS (0x00)
static uint8_t is_cmd_processing = 0;
static uint8_t cmd_buffer[CMD_BUFFER_SIZE] = {};

static void decode_command_header(const uint8_t *buffer);
static void decode_command(uint8_t cmd, const uint8_t *buffer, const uint16_t length);


void cmd_parser_submit_data(const uint8_t *buffer, const uint16_t length)
{
	if (!is_cmd_processing && buffer && length <= sizeof(cmd_buffer))
	{
		memcpy(cmd_buffer, buffer, length);
		is_cmd_processing = 1;
	}
}

void cmd_parser_process_command()
{
	if (is_cmd_processing)
	{
		const uint8_t cmd_type = cmd_buffer[0];

		if (cmd_type == TLOG_COMMAND)
		{
			decode_command_header(&cmd_buffer[1]);
		}
		else
		{
			is_cmd_processing = 0;
		}
	}
}

void decode_command_header(const uint8_t *buffer)
{
	const uint8_t cmd = buffer[0];
	uint16_t data_length = 0;
	memcpy(&data_length, &buffer[1], sizeof(data_length));

	if (data_length > sizeof(cmd_buffer) - CMD_HEADER_SIZE)
	{
		is_cmd_processing = 0;
	}
	else
	{
		decode_command(cmd, &buffer[3], data_length);
	}
}

void decode_command(uint8_t cmd, const uint8_t *buffer, const uint16_t length)
{
	if (cmd == GET_STATUS)
	{
		DBG_PRINTF("GetStatus");
	}

	is_cmd_processing = 0;
}
