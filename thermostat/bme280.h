/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Thermostat Project
 * 
 * Module: Temperature Sensor Driver Header
 * Author: Mark Grebe
 ****************************************************************************/

void bme280_init();
uint8_t bme280_read_chipid();
void bme280_read_data(float *temperature, float *humidity, uint32_t *pressure);
