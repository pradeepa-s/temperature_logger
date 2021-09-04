/*
 * dev_led.h
 *
 *  Created on: 29 Aug 2021
 *      Author: Pradeepa
 */

#ifndef INC_DEV_LED_H_
#define INC_DEV_LED_H_

#include <stdint.h>

void dev_led_indicate_alarm(uint8_t alarm);

void dev_led_low_done();
void dev_led_high_done();

#endif /* INC_DEV_LED_H_ */
