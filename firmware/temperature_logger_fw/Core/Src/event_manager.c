/*
 * event_manager.c
 *
 *  Created on: 4 Sep 2021
 *      Author: Pradeepa
 */

#include "event_manager.h"
#include "usart.h"

event_id events[2] = {DEVICE_EVENT_NONE, DEVICE_EVENT_NONE};

void submit_event(event_id event)
{
   //char done[] = "++5";
   //done[2] = 48 + event;
	//HAL_UART_Transmit(&huart1, (uint8_t*)done, sizeof(done), 0xFFFFFFFF);
    events[0] = event;
}

event_id get_next_event()
{
    event_id ev = events[0];

    if (ev != DEVICE_EVENT_NONE)
    {
		//char done[] = "<<5";
		//done[2] = 48 + ev;
		//HAL_UART_Transmit(&huart1, (uint8_t*)done, sizeof(done), 0xFFFFFFFF);
    }
	return ev;
}

event_id complete_event(event_id event)
{
    if (events[0] == event && event != DEVICE_EVENT_NONE)
    {
	   //char done[] = "--5";
		//done[2] = 48 + event;
		//HAL_UART_Transmit(&huart1, (uint8_t*)done, sizeof(done), 0xFFFFFFFF);
        events[0] = DEVICE_EVENT_NONE;
    }
    return DEVICE_EVENT_NONE;
}


