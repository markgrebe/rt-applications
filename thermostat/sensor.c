/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Thermostat Project
 * 
 * Module: Sensor Component Source
 * Author:
 ****************************************************************************/

#include <rtthread.h>
#include <pico/stdlib.h>
#include <hardware/i2c.h>
#include "bme280.h"
#include "sensor.h"

#define I2C_SDA_PIN (20)
#define I2C_SCL_PIN (21)

// Sensor Thread ID
static rt_thread_t sensor_tid = RT_NULL;

// Sensor shared memory mutex
static rt_mutex_t sensor_mutex;

// Sensor component shared memory variables to store
// Temperature, Pressure, and humidity
static float s_temperature;
static float s_humidity;
static uint32_t s_pressure;

void sensor_read_value(float *temperature,
                       float *humidity)
    {
    // FillMeIn
    // "Getter" function for the Sensor component that
    // allows an external component to read the sensor
    // variables.
    
    }

static void sensor_entry(void *parameter)
{
    rt_kprintf("Starting Sensor!\n");

    // FillMeIn
    // Sensor thread function.
    // It should run in an infinite loop, reading sensor data
    // into the sensor component shared memory variables
    // defined at the start of the file.
    // Then it should delay for 0.5 seconds before looping.

}

void sensor_init(void)
    {
    rt_kprintf("Starting Sensor Init!\n");

    // FillMeIn
    // The sensor needs to be initialized.
    // Create the Sensor Thread and the mutex to protect
    // the sensor shared memory area.


    // Initialize the Sensor driver.
    bme280_init(i2c0, I2C_SDA_PIN, I2C_SCL_PIN);

    rt_kprintf("Finished Sensor Init!\n");
    }

void sensor_start(void)
    {
    // FillMeIn
    // The Sensor thread needs to be started.

    rt_thread_startup(sensor_tid);
    }
