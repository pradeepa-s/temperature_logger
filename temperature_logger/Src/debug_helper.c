/*
 * debug_helper.c
 *
 *  Created on: Nov 26, 2017
 *      Author: PradeepaS
 */

#include <stdint.h>
#include "stm32l0xx_hal.h"

extern UART_HandleTypeDef huart1;

int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++){
		__io_putchar(*ptr++);
	}

	return len;

}

int __io_putchar(int ch)
{

	uint8_t data = (uint8_t) ch;

	uint16_t size = sizeof(data);

	uint32_t timeout = 1000;

	HAL_UART_Transmit(&huart1, &data, size, timeout);

	return 0;

}
