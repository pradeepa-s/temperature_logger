/*
 * dbg_printf.c
 *
 *  Created on: 3 Jul. 2023
 *      Author: prade
 */

#include "dbg_printf.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define DEBUG_MSG_BUFFER_SIZE (100)
#define DBG_MESSAGE_HEADER_SIZE (3)

static char dbg_msg_buf[DEBUG_MSG_BUFFER_SIZE] = {};
static uint8_t write_index = 0;
static uint8_t read_index = 0;
static uint16_t data_size = 0;

void dbg_printf_init()
{
	setbuf(stdout, NULL);
}

uint8_t dbg_printf_is_data_available()
{
	return data_size > 0;
}

uint16_t dbg_printf_get_data(uint8_t *out_buffer, const size_t size)
{
	// Header
	out_buffer[0] = 0x00;
	out_buffer[1] = data_size & 0x00FF;
	out_buffer[2] = (data_size >> 8) & 0x00FF;

	uint8_t *transmit_buffer = &out_buffer[3];
	if (write_index > read_index)
	{
		memcpy(transmit_buffer, &dbg_msg_buf[read_index], data_size);
	}
	else
	{
		const uint8_t end_size = DEBUG_MSG_BUFFER_SIZE - read_index;
		memcpy(transmit_buffer, &dbg_msg_buf[read_index], end_size);
		memcpy(&transmit_buffer[data_size], dbg_msg_buf, write_index);
	}

	read_index = (read_index + data_size) % DEBUG_MSG_BUFFER_SIZE;

	const uint16_t packet_size = data_size + DBG_MESSAGE_HEADER_SIZE;
	data_size = 0;

	return packet_size;
}

int __io_putchar(int ch)
{
	if (data_size < DEBUG_MSG_BUFFER_SIZE)
	{
		const uint8_t data = (uint8_t)ch;
		dbg_msg_buf[write_index] = data;
		write_index = (write_index + 1) % DEBUG_MSG_BUFFER_SIZE;
		data_size = data_size + 1;
	}
	return ch;
}
