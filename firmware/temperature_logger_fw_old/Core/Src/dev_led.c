/*
 * dev_led.c
 *
 *  Created on: 29 Aug 2021
 *      Author: Pradeepa
 */

#include "dev_led.h"
#include "dev_time.h"
#include "tim.h"
#include "dev_operation_tracker.h"

static void set_blink_count(uint8_t pattern);

static uint8_t blink_count = 0;

void dev_led_indicate_alarm(uint8_t alarm)
{
	if (alarm == DEV_ALARM_1_MINS)
	{
		set_blink_count(1);
	}
	else if (alarm == DEV_ALARM_15_MINS)
	{
		set_blink_count(2);
	}
	else if (alarm == DEV_ALARM_30_MINS)
	{
		set_blink_count(3);
	}
	else if (alarm == DEV_ALARM_60_MINS)
	{
		set_blink_count(4);
	}
	else
	{
		set_blink_count(8);
	}

	dev_operation_start(DEV_OPERATION_LED);
}


void set_blink_count(uint8_t count)
{
	if (count == 0)
	{
		return;
	}
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
	blink_count = count;
	HAL_TIM_Base_Init(&htim2);
	HAL_TIM_OC_Init(&htim2);
	HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim2);
}

void dev_led_low_done()
{
	if (blink_count > 0)
	{
		blink_count--;
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_TIM_OC_Stop_IT(&htim2, TIM_CHANNEL_1);
		HAL_TIM_Base_Stop_IT(&htim2);
		dev_operation_complete(DEV_OPERATION_LED);
	}

}

void dev_led_high_done()
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
}
