/*
 * dev_operation_tracker.h
 *
 *  Created on: 2 Sep 2021
 *      Author: Pradeepa
 */

#ifndef INC_DEV_OPERATION_TRACKER_H_
#define INC_DEV_OPERATION_TRACKER_H_

#include <stdint.h>

#define DEV_OPERATION_LED		(0x00)
#define DEV_OPERATION_BUTTON	(0x01)

void dev_operation_start(uint8_t operation);
void dev_operation_complete(uint8_t operation);
uint8_t dev_operation_is_pending();

#endif /* INC_DEV_OPERATION_TRACKER_H_ */
