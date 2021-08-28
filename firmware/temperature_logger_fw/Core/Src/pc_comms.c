/*
 * pc_comms.c
 *
 *  Created on: 28 Aug 2021
 *      Author: Pradeepa
 */

#include <stdio.h>
#include "pc_comms.h"
#include "usart.h"

void send_temperature_reading(const temperature_reading* reading)
{
    /*
       0x | datetime    | : | temperature in integer | \r | \n
       0x | max 8 chars | : | 7 chars                | \r | \n
   */
    uint8_t output[30];
    int length = sprintf(output, "0x%X:%d\n\r", reading->datetime, reading->value);
    HAL_UART_Transmit(&huart1, output, length, 0xFFFFFFFF);
}
