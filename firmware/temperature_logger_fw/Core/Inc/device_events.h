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

typedef void (*event_cb)(uint32_t event_id);

#endif /* INC_DEVICE_EVENTS_H_ */
