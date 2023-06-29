/*
 * led.h
 *
 *  Created on: 1 Aug 2021
 *      Author: Pradeepa
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h>

typedef enum
{
	TMP_LOG_LED_GREEN,
	TMP_LOG_LED_RED
} TMP_LOG_LED;

typedef enum
{
	TMP_LOG_LED_STATE_ON,
	TMP_LOG_LED_STATE_OFF
} TMP_LOG_LED_STATE;

void set_led(TMP_LOG_LED led, TMP_LOG_LED_STATE state);

#endif /* INC_LED_H_ */
