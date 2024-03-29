/*
 * dev_time.h
 *
 *  Created on: 28 Aug 2021
 *      Author: Pradeepa
 */

#ifndef INC_DEV_TIME_H_
#define INC_DEV_TIME_H_

#include <stdint.h>
#include "device_events.h"

#define DEV_ALARM_NONE      (0x00)
#define DEV_ALARM_1_MINS	(0x01 << 0)
#define DEV_ALARM_15_MINS	(0x01 << 1)
#define DEV_ALARM_30_MINS	(0x01 << 2)
#define DEV_ALARM_60_MINS	(0x01 << 3)

typedef struct {
	unsigned int year;
	unsigned short month;
	unsigned short date;
	unsigned short hour;
	unsigned short minute;
	unsigned short second;
} datetime;

void dev_time_init(event_cb cb);
void dev_time_set(uint8_t yy, uint8_t mm, uint8_t dd, uint8_t hh, uint8_t min, uint8_t ss);
uint8_t dev_time_alarm_change();
uint8_t dev_time_get_alarm();
void rtc_alarm_elapsed();
void get_datetime(datetime* ts);

void set_next_alarm();

#endif /* INC_DEV_TIME_H_ */
