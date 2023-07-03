/*
 * dbg_printf.c
 *
 *  Created on: 3 Jul. 2023
 *      Author: prade
 */

#include "debug_printf.h"
#include <stdio.h>
#include "usart.h"


void dbg_printf(const char *format, ...)
{
	printf(format);
}

int __io_putchar(int ch)
{
	const uint8_t data = (uint8_t)ch;
	HAL_UART_Transmit(&huart1, &data, sizeof(data), 0xFFFFFFFF);
	return ch;
}
