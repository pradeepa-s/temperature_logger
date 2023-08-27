/*
 * command_parser.c
 *
 *  Created on: Aug 12, 2023
 *      Author: prade
 */

#include "command_parser.h"
#include "dbg_printf.h"
#include "response_generator.h"
#include <string.h>

#define CMD_BUFFER_SIZE (16)
#define TLOG_COMMAND (0x01)
#define CMD_HEADER_SIZE (3)

// Data packet indexes
#define CMD_TYPE_INDEX (0)
#define CMD_LENGTH_INDEX (1)
#define CMD_DATA_INDEX (3)

// Command codes
#define GET_STATUS_CMD (0x00)
#define SET_DATETIME_CMD (0x01)

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
		const uint8_t cmd_type = cmd_buffer[CMD_TYPE_INDEX];

		if (cmd_type == TLOG_COMMAND)
		{
			decode_command_header(&cmd_buffer[CMD_LENGTH_INDEX]);
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
		decode_command(cmd, &buffer[CMD_DATA_INDEX], data_length);
	}
}

void decode_command(uint8_t cmd, const uint8_t *buffer, const uint16_t length)
{
	if (cmd == GET_STATUS_CMD)
	{
		rg_generate_get_status_response();
	}
	else if (cmd == SET_DATETIME_CMD)
	{
		rg_process_set_datetime_cmd(buffer, length);
	}

	is_cmd_processing = 0;
}
