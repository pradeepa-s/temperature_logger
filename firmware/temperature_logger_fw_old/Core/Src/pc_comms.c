/*
 * pc_comms.c
 *
 *  Created on: 28 Aug 2021
 *      Author: Pradeepa
 */

#include <stdio.h>
#include "pc_comms.h"
#include "usart.h"

static uint8_t recieve_buffer[20];

static uint8_t star_count = 0;
uint8_t next_read_size = 1;
uint8_t reading_time = 0;

static event_cb device_event_cb;

uint8_t pc_comms_yy = 0;
uint8_t pc_comms_mm = 0;
uint8_t pc_comms_dd = 0;
uint8_t pc_comms_hh = 0;
uint8_t pc_comms_min = 0;
uint8_t pc_comms_ss = 0;

static void process(uint8_t index);

void pc_comms_init(event_cb cb)
{
	device_event_cb = cb;
	HAL_UART_Receive_IT(&huart1, recieve_buffer, next_read_size);
}

void data_received_from_pc()
{
	process(0);
	HAL_UART_Receive_IT(&huart1, &recieve_buffer[0], next_read_size);
}

void process(uint8_t index)
{
	next_read_size = 1;
	if (reading_time)
	{
		pc_comms_yy = recieve_buffer[0];
		pc_comms_mm = recieve_buffer[1];
		pc_comms_dd = recieve_buffer[2];
		pc_comms_hh = recieve_buffer[3];
		pc_comms_min = recieve_buffer[4];
		pc_comms_ss = recieve_buffer[5];
        reading_time = 0;
        star_count = 0;
        device_event_cb(DEVICE_EVENT_UPDATE_TIME);
	}

	if (recieve_buffer[index] == '*')
	{
		star_count++;
	}
	else if (star_count == 5)
	{
		if (recieve_buffer[index] == 'E')
		{
			// Chip erase
			device_event_cb(DEVICE_EVENT_CHIP_ERASE);
			star_count = 0;
		}
		else if (recieve_buffer[index] == 'R')
		{
			// Chip read
			device_event_cb(DEVICE_EVENT_CHIP_READ);
			star_count = 0;
		}
		else if (recieve_buffer[index] == 'T')
		{
			// Chip read
			reading_time = 1;
			next_read_size = 6;
		}
		else if (recieve_buffer[index] == 'S')
		{
			// Chip read
			device_event_cb(DEVICE_EVENT_GET_STATE);
			star_count = 0;
		}
	}
	else
	{
		star_count = 0;
	}
}
