/*
 * button.h
 *
 *  Created on: 13 Aug 2021
 *      Author: Pradeepa
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "device_events.h"

void process_button_event(void);
void button_init(event_cb cb);

#endif /* INC_BUTTON_H_ */
