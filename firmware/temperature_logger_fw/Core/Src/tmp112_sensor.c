#include "tmp112_sensor.h"
#include <string.h>


static double transform_to_centigrades(uint8_t* register_data);
static tmp112_tx_func i2c_tx = 0;
static tmp112_rx_func i2c_rx = 0;
static uint8_t slave_address = 0;


void tmp112_sensor_init(uint8_t slave_addr, tmp112_tx_func tx, tmp112_rx_func rx)
{
    i2c_tx = tx;
    i2c_rx = rx;
    slave_address = slave_addr;
}

void tmp112_sensor_deinit()
{
    i2c_tx = 0;
    i2c_rx = 0;
    slave_address = 0;
}

double tmp112_sensor_get_temperature()
{
    uint8_t write_data = 0x00;
    i2c_tx(slave_address, &write_data, 1);

    uint8_t read_data[2];
    i2c_rx(slave_address, read_data, 2);

    return transform_to_centigrades(read_data);
}

double transform_to_centigrades(uint8_t* register_data)
{
    const uint16_t msb = register_data[0] << 4;
    const uint16_t lsb = register_data[1] >> 4;

    uint16_t temperature_word = (msb & 0x0FF0) | (lsb & 0x000F) ;
    int32_t val_before_resolution = temperature_word;

    if (temperature_word & 0x800)
    {
    	temperature_word = ((~temperature_word) & 0xFFF) + 1;
        val_before_resolution = -1 * temperature_word;
    }
    return val_before_resolution * 0.0625;
}
