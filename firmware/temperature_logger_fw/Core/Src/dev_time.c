/*
 * dev_time.c
 *
 *  Created on: 28 Aug 2021
 *      Author: Pradeepa
 */

#include "dev_time.h"
#include "rtc.h"
#include <time.h>

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
	c_time.tm_mon = curr_date.Month;
	c_time.tm_year = 2000 + curr_date.Year - 1900;
	c_time.tm_wday = curr_date.WeekDay;

	time_t time_val = mktime(&c_time);

	return time_val;
}


