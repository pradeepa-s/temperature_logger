/*
 * debug_helper.c
 *
 *  Created on: Nov 26, 2017
 *      Author: PradeepaS
 */

#include <stdint.h>
#include "stm32l0xx_hal.h"

extern UART_HandleTypeDef huart1;

int __io_putchar(int ch)
{

	uint8_t data = (uint8_t) ch;

	uint16_t size = sizeof(data);

	uint32_t timeout = 1000;

	HAL_UART_Transmit(&huart1, &data, size, timeout);

	return 0;

}

int __io_getchar(void)
{
	uint8_t data;

	uint16_t size = sizeof(data);

	uint32_t timeout = 0xFFFFFFFF;

	HAL_UART_Receive(&huart1, &data, size, timeout);
	HAL_UART_Transmit(&huart1, &data, size, timeout);

	return data;
}
