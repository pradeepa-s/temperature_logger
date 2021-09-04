/*
 * event_manager.h
 *
 *  Created on: 4 Sep 2021
 *      Author: Pradeepa
 */

#ifndef INC_EVENT_MANAGER_H_
#define INC_EVENT_MANAGER_H_

#include "device_events.h"

void submit_event(event_id event);
event_id get_next_event();
event_id complete_event(event_id event);

#endif /* INC_EVENT_MANAGER_H_ */
