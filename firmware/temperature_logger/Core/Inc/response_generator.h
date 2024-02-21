/*
 * response_generator.h
 *
 *  Created on: Aug 18, 2023
 *      Author: prade
 */

#ifndef INC_RESPONSE_GENERATOR_H_
#define INC_RESPONSE_GENERATOR_H_

#include <stdint.h>
#include <stddef.h>

void rg_generate_get_status_response();
void rg_process_set_datetime_cmd(const uint8_t* buffer, const uint16_t length);
void rg_generate_chip_erase_response();

uint8_t rg_is_response_ready();
uint16_t rg_read_response(uint8_t *buffer, const size_t length);

#endif /* INC_RESPONSE_GENERATOR_H_ */
