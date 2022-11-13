/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Thermostat Project
 * 
 * Module: Control Component Source
 * Author:
 ****************************************************************************/
#include <rtthread.h>
#include "sensor.h"
#include "control.h"

#define TEMP_DELTA                      (0.5)

// Control Thread ID
static rt_thread_t control_tid = RT_NULL;

// Control shared memory mutex
static rt_mutex_t control_mutex;

// Control Thread Message Queue
rt_mq_t control_msgq;

// Sensor component shared memory variables to store
// Set Temperatures and Mode
static float cool_set_temperature;
static float heat_set_temperature;
static HVACMode set_mode;

static float temperature;

// Sensor component shared memory variables to store
// Control component status variables.
static int cool_on;
static int heat_on;
static int fan_on;

float control_get_cool_temperature(void)
    {
    // FillMeIn
    // "Getter" function for the Control component that
    // allows an external component to read the Control
    // cool set temperature variables.

    return(cool_set_temperature);
    }

float control_get_heat_temperature(void)
    {
    // FillMeIn
    // "Getter" function for the Control component that
    // allows an external component to read the Control
    // heat set temperature variables.

    return(heat_set_temperature);
    }

void control_get_status(HVACMode *mode,
                        int *cool_status, 
                        int *heat_status, 
                        int *fan_status)
    {
    // FillMeIn
    // "Getter" function for the Control component that
    // allows an external component to read the Control
    // status variables.

    }

static void control_entry(void *parameter)
{
    rt_kprintf("Starting Control!\n");

    // FillMeIn
    // Control thread function.
    // It should run in an infinite loop, reading any
    // available messages from the control_msgq, then
    // checking current temperature and set temperatures,
    // then turning Heater and AC on/off based on the
    // following alorithm:
    // 
    // If in heat mode
    //    If heater off
    //         If (temperature < (heat_set_temperature - 0.5))
    //             Turn heater on
    //    Else
    //         If (temperature > (heat_set_temperature + 0.5))
    //             Turn heater off
    // Else
    //    If AC off
    //         If (temperature > (cool_set_temperature + 0.5))
    //             Turn AC on
    //    Else
    //         If (temperature < (cool_set_temperature - 0.5))
    //             Turn AC off
    //
    // Then it should delay for 0.5 seconds before looping.

}

void control_init(void)
    {
    rt_kprintf("Starting Control Init!\n");

    // FillMeIn
    // The Control component needs to be initialized.
    // Create the Control Thread, the mutex to protect
    // the Control shared memory area, and the
    // Control message queue for key input.

    }

void control_start(void)
    {
    // FillMeIn
    // The Control thread needs to be started.

    }
