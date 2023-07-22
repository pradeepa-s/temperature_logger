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
