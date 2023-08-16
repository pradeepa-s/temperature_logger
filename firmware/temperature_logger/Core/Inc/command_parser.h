/*
 * command_parser.h
 *
 *  Created on: Aug 12, 2023
 *      Author: prade
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_

#include <stdint.h>

void cmd_parser_submit_data(const uint8_t *buffer, const uint16_t length);
void cmd_parser_process_command();

#endif /* INC_COMMAND_PARSER_H_ */
