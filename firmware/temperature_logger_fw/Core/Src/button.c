/*
 * button.c
 *
 *  Created on: 13 Aug 2021
 *      Author: Pradeepa
 */

#include "button.h"
#include "gpio.h"

static void button_pressed();
static void button_depressed();

static uint8_t pressed = 0;
static event_cb callback_func = 0;

void button_init(event_cb cb)
{
	callback_func = cb;
}

void process_button_event()
{
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin);
	if (pin_state == GPIO_PIN_SET)
	{
		button_pressed();
	}
	else
	{
		button_depressed();
	}
}

void button_pressed()
{
	pressed = 1;
}

void button_depressed()
{
	if (pressed)
	{
		callback_func(DEVICE_EVENT_SINGLE_BUTTON_PRESS);
	}
	pressed = 0;
}
