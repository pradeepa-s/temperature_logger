/*
 * transport_layer.h
 *
 *  Created on: Jul 30, 2023
 *      Author: prade
 */

#ifndef INC_TRANSPORT_LAYER_H_
#define INC_TRANSPORT_LAYER_H_

#include <stdint.h>
#include <stddef.h>

typedef void (*TL_PACKET_COMPLETE_CB)();

typedef uint8_t (*TL_DATA_STATUS_FUNC)();
typedef uint16_t (*TL_DATA_READ_FUNC)(uint8_t *buffer, size_t length);

void tl_add_tx_data_provider(TL_DATA_STATUS_FUNC is_pending, TL_DATA_READ_FUNC read_data);
void tl_poll_for_tx_data();
void tl_init_rx(TL_PACKET_COMPLETE_CB cb);

#endif /* INC_TRANSPORT_LAYER_H_ */
