/*
 * pc_comms.h
 *
 *  Created on: 28 Aug 2021
 *      Author: Pradeepa
 */

#ifndef INC_PC_COMMS_H_
#define INC_PC_COMMS_H_

#include "storage.h"
#include "device_events.h"

extern uint8_t pc_comms_yy;
extern uint8_t pc_comms_mm;
extern uint8_t pc_comms_dd;
extern uint8_t pc_comms_hh;
extern uint8_t pc_comms_min;
extern uint8_t pc_comms_ss;

void pc_comms_init(event_cb cb);
void data_received_from_pc();

#endif /* INC_PC_COMMS_H_ */
