/*
 * device_events.h
 *
 *  Created on: 13 Aug 2021
 *      Author: Pradeepa
 */

#ifndef INC_DEVICE_EVENTS_H_
#define INC_DEVICE_EVENTS_H_

typedef enum _event_id
{
    DEVICE_EVENT_NONE,
    DEVICE_EVENT_SINGLE_BUTTON_PRESS,
    DEVICE_EVENT_LONG_BUTTON_PRESS,
    DEVICE_EVENT_CHIP_READ,
    DEVICE_EVENT_GET_STATE,
    DEVICE_EVENT_RTC_ALARM_ELAPSED,
    DEVICE_EVENT_CHIP_ERASE,
    DEVICE_EVENT_UPDATE_TIME
} event_id;

typedef void (*event_cb)(event_id ev);

#endif /* INC_DEVICE_EVENTS_H_ */
