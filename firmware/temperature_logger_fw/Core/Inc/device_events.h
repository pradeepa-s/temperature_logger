/*
 * device_events.h
 *
 *  Created on: 13 Aug 2021
 *      Author: Pradeepa
 */

#ifndef INC_DEVICE_EVENTS_H_
#define INC_DEVICE_EVENTS_H_

#include <stdint.h>

#define DEVICE_EVENT_SINGLE_BUTTON_PRESS  (1)
#define DEVICE_EVENT_LONG_BUTTON_PRESS    (2)
#define DEVICE_EVENT_RTC_ALARM_ELAPSED    (3)
#define DEVICE_EVENT_CHIP_ERASE			  (4)
#define DEVICE_EVENT_CHIP_READ			  (5)
#define DEVICE_EVENT_UPDATE_TIME          (6)

typedef void (*event_cb)(uint32_t event_id);

#endif /* INC_DEVICE_EVENTS_H_ */
