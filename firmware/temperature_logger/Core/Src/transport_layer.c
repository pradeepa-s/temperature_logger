/*
 * transport_layer.c
 *
 *  Created on: Jul 30, 2023
 *      Author: prade
 */

#include "transport_layer.h"
#include <string.h>
#include "usart.h"

#define TL_RX_DATA_SIZE (256)
#define TL_TX_HEADER_SIZE (3)
#define TL_TX_DATA_SIZE (256)
#define TL_SOH (0x01)

#define MAX_PRESENTATION_LAYERS (2)

typedef struct{
	TL_DATA_STATUS_FUNC is_data_available;
	TL_DATA_READ_FUNC read_data;
} TL_TX_PROVIDER;

static uint8_t tx_is_busy = 0;
static uint8_t tx_data_provider_count = 0;
static TL_TX_PROVIDER tx_data_providers[MAX_PRESENTATION_LAYERS];
// Alignment is needed as this buffer is a DMA buffer
static uint8_t tx_buffer[TL_TX_DATA_SIZE + TL_TX_HEADER_SIZE] __attribute__((aligned(8)))= {};

enum TL_RX_STATE{
	TL_WAITING_FOR_SOH,
	TL_WAITING_FOR_LENGTH_LSB,
	TL_WAITING_FOR_LENGTH_MSB,
	TL_WAITING_FOR_DATA
} state = TL_WAITING_FOR_SOH;
static uint8_t rx_buffer[TL_RX_DATA_SIZE] = {};
static uint16_t rx_length = 0;
static uint16_t write_index = 0;
static uint8_t rx_byte = 0;
static TL_PACKET_COMPLETE_CB rx_completed;

static void rx_reset();
static void tl_start_rx();

void tl_add_tx_data_provider(TL_DATA_STATUS_FUNC is_pending, TL_DATA_READ_FUNC read_data)
{
	if (tx_data_provider_count < MAX_PRESENTATION_LAYERS)
	{
		tx_data_providers[tx_data_provider_count].is_data_available = is_pending;
		tx_data_providers[tx_data_provider_count].read_data = read_data;

		tx_data_provider_count++;
	}
}

void tl_poll_for_tx_data()
{
	if (tx_is_busy)
	{
		return;
	}

	for (int i = 0; i < tx_data_provider_count; i++)
	{
		if (tx_data_providers[i].is_data_available())
		{
			tx_is_busy = 1;

			tx_buffer[0] = TL_SOH;

			uint16_t length = tx_data_providers[i].read_data(&tx_buffer[3], TL_TX_DATA_SIZE);

			tx_buffer[1] = length & 0x00FF;
			tx_buffer[2] = (length >> 8) & 0x00FF;

			HAL_UART_Transmit_DMA(&huart1, (const uint8_t*)&tx_buffer, length + TL_TX_HEADER_SIZE);
		}
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	tx_is_busy = 0;
}

void tl_init_rx(TL_PACKET_COMPLETE_CB cb)
{
	rx_completed = cb;
	tl_start_rx();
}

void tl_start_rx()
{
	HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (state == TL_WAITING_FOR_SOH && rx_byte == TL_SOH)
	{
		state = TL_WAITING_FOR_LENGTH_LSB;
	}
	else if (state == TL_WAITING_FOR_LENGTH_LSB)
	{
		rx_length = rx_byte;
		state = TL_WAITING_FOR_LENGTH_MSB;
	}
	else if (state == TL_WAITING_FOR_LENGTH_MSB)
	{
		rx_length |= (rx_byte << 8);
		if (rx_length < TL_RX_DATA_SIZE)
		{
			state = TL_WAITING_FOR_DATA;
		}
		else
		{
			rx_reset();
		}

	}
	else if (state == TL_WAITING_FOR_DATA && rx_length > 0)
	{
		rx_buffer[write_index] = rx_byte;
		write_index++;

		if (rx_length == write_index)
		{
			rx_completed(rx_buffer, rx_length);
			rx_reset();
		}
	}
	else
	{
		rx_reset();
	}

	tl_start_rx();
}

void rx_reset()
{
	rx_length = 0;
	write_index = 0;
	state = TL_WAITING_FOR_SOH;
}
