/*
 * button.c
 *
 *  Created on: 13 Aug 2021
 *      Author: Pradeepa
 */

#include "button.h"
#include "gpio.h"
#include "tim.h"
#include "dev_operation_tracker.h"

static void button_pressed();
static void button_depressed();

static uint8_t single_press_started = 0;
static uint8_t press_and_hold_time = 0;
static event_cb callback_func = 0;

void button_init(event_cb cb)
{
	callback_func = cb;
	press_and_hold_time = 0;
	single_press_started = 0;
}

void process_button_event()
{
	dev_operation_start(DEV_OPERATION_BUTTON);
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

void button_press_and_hold()
{
	single_press_started = 0;
	press_and_hold_time++;

	if (press_and_hold_time % 3 == 0)
	{
		callback_func(DEVICE_EVENT_LONG_BUTTON_PRESS);
	}
}

void button_pressed()
{
	single_press_started = 1;
	press_and_hold_time = 0;

	HAL_TIM_OC_Start_IT(&htim21, TIM_CHANNEL_1);
}

void button_depressed()
{
	if (single_press_started)
	{
		callback_func(DEVICE_EVENT_SINGLE_BUTTON_PRESS);
	}

	single_press_started = 0;
	HAL_TIM_OC_Stop_IT(&htim21, TIM_CHANNEL_1);
	HAL_TIM_OC_Init(&htim21);
}
