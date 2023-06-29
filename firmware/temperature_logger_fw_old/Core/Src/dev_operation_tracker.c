/*
 * dev_operation_tracker.c
 *
 *  Created on: 2 Sep 2021
 *      Author: Pradeepa
 */

#include "dev_operation_tracker.h"

static uint8_t operation_state[2] = {0, 0};

void dev_operation_start(uint8_t operation)
{
	operation_state[operation] = 1;
}

void dev_operation_complete(uint8_t operation)
{
	operation_state[operation] = 0;
}

uint8_t dev_operation_is_pending()
{
	for (int i = 0; i < sizeof(operation_state); i++)
	{
		if (operation_state[i])
		{
			return 1;
		}
	}

	return 0;
}
