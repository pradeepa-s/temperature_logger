/*
 * debug_printf.h
 *
 *  Created on: 3 Jul. 2023
 *      Author: prade
 */

#ifndef INC_DBG_PRINTF_H_
#define INC_DBG_PRINTF_H_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define USE_DBG_PRINTF

#ifdef USE_DBG_PRINTF
#define DBG_PRINTF(...) printf(__VA_ARGS__)
#else
#define DBG_PRINTF(...)
#endif

void dbg_printf_init();
uint8_t dbg_printf_is_data_available();
uint16_t dbg_printf_get_data(uint8_t *out_buffer, size_t size);

#endif /* INC_DBG_PRINTF_H_ */
