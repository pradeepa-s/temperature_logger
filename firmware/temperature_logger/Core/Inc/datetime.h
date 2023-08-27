/*
 * datetime.h
 *
 *  Created on: Jul 22, 2023
 *      Author: prade
 */

#ifndef INC_DATETIME_H_
#define INC_DATETIME_H_

#include <stdint.h>

typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t date;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} datetime;

datetime get_datetime();
int set_datetime(const datetime dt);

#endif /* INC_DATETIME_H_ */
