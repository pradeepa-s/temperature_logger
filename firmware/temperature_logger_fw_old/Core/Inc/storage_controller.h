/*
 * storage_controller.h
 *
 *  Created on: 18 Nov. 2022
 *      Author: Pradeepa
 */

#ifndef INC_STORAGE_CONTROLLER_H_
#define INC_STORAGE_CONTROLLER_H_

#include <stdint.h>
#include <stddef.h>
#include "dev_time.h"

typedef enum {
	storge_status_OK
}storage_status;

typedef int temperature;

typedef struct {
	temperature tr;
	datetime dt;
} storage_entry;

void storage_controller_init();
storage_status flash_storage_erase_full();
storage_status flash_storage_write(storage_entry *entries, uint8_t count);
void flash_storage_read_start();
unsigned int flash_storage_read(storage_entry *entries, uint8_t count);

#endif /* INC_STORAGE_CONTROLLER_H_ */
