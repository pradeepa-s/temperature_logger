/*
 * dbg_printf.c
 *
 *  Created on: 3 Jul. 2023
 *      Author: prade
 */

#include "debug_printf.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"

#define DEBUG_MSG_BUFFER_SIZE (100)

static uint8_t dbg_msg_buf[DEBUG_MSG_BUFFER_SIZE] = {};
static uint8_t transmit_buffer[DEBUG_MSG_BUFFER_SIZE] = {};
static uint8_t write_index = 0;
static uint8_t read_index = 0;
static uint8_t data_size = 0;
static uint8_t is_transmit_pending = 0;

void dbg_printf(const char *format, ...)
{
	printf(format);
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

void run_uart_scheduler()
{
	const uint8_t is_data_pending = (data_size > 0);

	if (!is_transmit_pending && is_data_pending)
	{
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
		is_transmit_pending = 1;
		HAL_UART_Transmit_IT(&huart1, transmit_buffer, data_size);
		data_size = 0;
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (write_index == read_index)
	{
		write_index = 0;
		read_index = 0;
	}
	is_transmit_pending = 0;
}

void wait()
{
	while(is_transmit_pending);
}
