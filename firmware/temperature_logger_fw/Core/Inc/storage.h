/*
 * storage.h
 *
 *  Created on: 15 Aug 2021
 *      Author: Pradeepa
 */

#ifndef INC_STORAGE_H_
#define INC_STORAGE_H_

#include <stdint.h>
#include <stddef.h>

#define _MAXIMUM_READ_COUNT		(10)

typedef struct _reading
{
	uint32_t datetime;
	int32_t value;
} temperature_reading;

typedef struct _values
{
	size_t count;
	temperature_reading readings[_MAXIMUM_READ_COUNT];
} storage_values;

uint8_t storage_write(temperature_reading data);

const storage_values* storage_read(uint32_t datetime);
const storage_values* storage_read_start();
const storage_values* storage_read_cont();

void erase_first_sector();
void storage_erase_full();

#endif /* INC_STORAGE_H_ */
