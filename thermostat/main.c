/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Thermostat Project
 * 
 * Module: Main Source
 * Author:
 ****************************************************************************/

#include <rtthread.h>
#include <rtdevice.h>
#include "gui.h"
#include "input.h"
#include "sensor.h"
#include "control.h"

int main(void)
{
    rt_kprintf("Hello, Thermostat User!\n");

    // Initialize each of the components.
    gui_init();
    input_init();
    sensor_init();
    control_init();

    // Start the components with threads.
    sensor_start();
    control_start();
    gui_start();

    while (1)
        {
        rt_thread_mdelay(1000);
        }
}

