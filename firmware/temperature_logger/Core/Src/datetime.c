/*
 * datetime.c
 *
 *  Created on: Jul 22, 2023
 *      Author: prade
 */

#include "datetime.h"
#include "rtc.h"

datetime get_datetime()
{
	datetime dt = {};

	RTC_TimeTypeDef time = {};
	RTC_DateTypeDef date = {};
	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

	dt.year = date.Year;
	dt.month = date.Month;
	dt.date = date.Date;
	dt.hour = time.Hours;
	dt.minute = time.Minutes;
	dt.second = time.Seconds;

	return dt;
}

int set_datetime(const datetime dt)
{
	if ((dt.date < 1 || dt.date > 31) || (dt.month < 1 || dt.month > 12) ||
			(dt.year > 99) || (dt.hour > 23) || (dt.minute > 59) || (dt.second > 59))
	{
		return -1;
	}

	RTC_TimeTypeDef time = {.Hours=dt.hour, .Minutes=dt.minute, .Seconds=dt.second};
	RTC_DateTypeDef date = {.Year=dt.year, .Month=dt.month, .Date=dt.date};

	HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);

	return 0;
}
