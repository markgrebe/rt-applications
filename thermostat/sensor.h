/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Thermostat Project
 * 
 * Module: Sensor Component Header
 * Author:
 ****************************************************************************/

void sensor_init(void);
void sensor_start(void);
void sensor_read_value(float *temperature,
                       float *humidity);
