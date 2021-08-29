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

uint32_t get_epoch_timestamp();
void init_next_temperature_log_time();
void rtc_alarm_elapsed();
void dev_time_init(event_cb cb);
void set_next_alarm();
void dev_time_set(uint8_t yy, uint8_t mm, uint8_t dd, uint8_t hh, uint8_t min, uint8_t ss);

#endif /* INC_DEV_TIME_H_ */
