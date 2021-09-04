/*
 * event_manager.c
 *
 *  Created on: 4 Sep 2021
 *      Author: Pradeepa
 */

#include "event_manager.h"

event_id events[2] = {DEVICE_EVENT_NONE, DEVICE_EVENT_NONE};

void submit_event(event_id event)
{
    events[0] = event;
}

event_id get_next_event()
{
    event_id ev = events[0];
    events[0] = DEVICE_EVENT_NONE;
	return ev;
}

event_id complete_event(event_id event)
{
    if (DEVICE_EVENT_NONE != event)
    {
        events[0] = DEVICE_EVENT_NONE;
    }
    return DEVICE_EVENT_NONE;
}


