/*
 * dev_time.c
 *
 *  Created on: 28 Aug 2021
 *      Author: Pradeepa
 */

#include "dev_time.h"
#include "rtc.h"
#include <time.h>
#include <stdio.h>
#include "usart.h"

static void set_next_temperature_log_time(uint8_t hour, uint8_t minute, uint8_t second);
static event_cb device_event_cb = 0;

static uint8_t current_alarm = 0;

void rtc_alarm_elapsed()
{
    device_event_cb(DEVICE_EVENT_RTC_ALARM_ELAPSED);
}

uint32_t get_epoch_timestamp()
{
	RTC_TimeTypeDef curr_time;
	RTC_DateTypeDef curr_date;
	HAL_RTC_GetDate(&hrtc,  &curr_date, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc,  &curr_time, RTC_FORMAT_BIN);

	struct tm c_time;

	c_time.tm_sec = curr_time.Seconds;
	c_time.tm_min = curr_time.Minutes;
	c_time.tm_hour = curr_time.Hours;
	c_time.tm_mday = curr_date.Date;
	c_time.tm_mon = curr_date.Month - 1;
	c_time.tm_year = 2000 + curr_date.Year - 1900;
	c_time.tm_wday = curr_date.WeekDay;

	time_t time_val = mktime(&c_time);

	return time_val;
}

void dev_time_init(event_cb cb)
{
    device_event_cb = cb;
    set_next_alarm();
}

uint8_t dev_time_alarm_change()
{
	if (current_alarm == 0x00)
	{
		current_alarm = DEV_ALARM_1_MINS;
	}
	else if (current_alarm == DEV_ALARM_60_MINS)
	{
		current_alarm = 0x00;
	}
	else
	{
		current_alarm = current_alarm << 1;
	}

	set_next_alarm();

	return current_alarm;
}

uint8_t dev_time_get_alarm()
{
	return current_alarm;
}

void set_next_alarm()
{
	RTC_TimeTypeDef curr_time;
	RTC_DateTypeDef curr_date;
	HAL_RTC_GetDate(&hrtc,  &curr_date, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc,  &curr_time, RTC_FORMAT_BIN);

	uint8_t interval = 0;
	if (current_alarm == DEV_ALARM_1_MINS)
	{
		interval = 1;
	}
	else if (current_alarm == DEV_ALARM_15_MINS)
	{
		interval = 15;
	}
	else if (current_alarm == DEV_ALARM_30_MINS)
	{
		interval = 30;
	}
	else if (current_alarm == DEV_ALARM_60_MINS)
	{
		interval = 60;
	}

	if (interval > 0)
	{
		uint8_t alarm_minutes = (curr_time.Minutes + interval) % 60;
		set_next_temperature_log_time(0, alarm_minutes, 0);
	}
	else
	{
		HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A);
	}
}

void dev_time_set(uint8_t yy, uint8_t mm, uint8_t dd, uint8_t hh, uint8_t min, uint8_t ss)
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	sTime.Hours = hh;
	sTime.Minutes = min;
	sTime.Seconds = ss;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
	sDate.Month = mm;
	sDate.Date = dd;
	sDate.Year = yy;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

void set_next_temperature_log_time(uint8_t hour, uint8_t minute, uint8_t second)
{
	RTC_AlarmTypeDef alarm = {0};

	alarm.AlarmTime.Hours = 0;
	alarm.AlarmTime.Minutes = minute;
	alarm.AlarmTime.Seconds = 0;
	alarm.AlarmTime.SubSeconds = 0;
	alarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	alarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	alarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY | RTC_ALARMMASK_HOURS;
	alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	alarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY;
	alarm.AlarmDateWeekDay = 1;
	alarm.Alarm = RTC_ALARM_A;

	HAL_RTC_SetAlarm_IT(&hrtc, &alarm, RTC_FORMAT_BIN);
}

