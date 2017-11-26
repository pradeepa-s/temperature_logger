/*
 * internal_clock_mgt.c
 *
 *  Created on: Nov 26, 2017
 *      Author: PradeepaS
 */

#include "internal_clock_mgt.h"
#include "stm32l0xx_hal.h"

extern RTC_AlarmTypeDef sAlarm;
extern RTC_TimeTypeDef current_time;
extern RTC_DateTypeDef current_date;
extern RTC_HandleTypeDef hrtc;

void show_time(void)
{
	HAL_RTC_GetTime(&hrtc, &current_time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &current_date, RTC_FORMAT_BIN);

	printf("Date: %d:%d:%d\r\n", current_date.Year, current_date.Month, current_date.Date);
	printf("Time: %d:%d:%d\r\n", current_time.Hours, current_time.Minutes, current_time.Seconds);
}

void set_alarm(void)
{
	HAL_RTC_GetTime(&hrtc, &current_time, RTC_FORMAT_BIN);
	  HAL_RTC_GetDate(&hrtc, &current_date, RTC_FORMAT_BIN);

	  /**Enable the Alarm A
	      */

	  current_time.Seconds += 1;

	  if(current_time.Seconds > 59){
		  current_time.Seconds -= 60;

		  current_time.Minutes += 1;

		  if(current_time.Minutes > 59){
			  current_time.Minutes -= 60;

			  current_time.Hours += 1;

			  if(current_time.Hours > 23){
				  current_time.Hours -= 24;
			  }
		  }
	  }

	  sAlarm.AlarmTime.Hours = current_time.Hours;
	  sAlarm.AlarmTime.Minutes = current_time.Minutes;
	  sAlarm.AlarmTime.Seconds = current_time.Seconds;
	  sAlarm.AlarmTime.SubSeconds = 0;
	  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
	  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	  sAlarm.AlarmDateWeekDay = 1;
	  sAlarm.Alarm = RTC_ALARM_A;
	  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
	  {
		  _Error_Handler(__FILE__, __LINE__);
	  }

	  printf("Alarm updated -> %d:%d:%d\r\n",
			  sAlarm.AlarmTime.Hours,
			  sAlarm.AlarmTime.Minutes,
			  sAlarm.AlarmTime.Seconds);
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	printf("\033c");
	printf("Alarm!!!\r\n");
	show_time();
	set_alarm();
}
