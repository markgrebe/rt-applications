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
#include "widget.h"

// Widgit Thread ID
static rt_thread_t widgit_tid = RT_NULL;

// Widgit shared memory mutex
static rt_mutex_t widgit_mutex;

static int value1 = 100;
static int value2 = 0;

void widgit_read_vals(int *val1,
                      int *val2)
    {
    // FillMeIn
    // "Getter" function for the Widgit component that
    // allows an external component to read the sensor
    // variables.
    rt_mutex_take(widgit_mutex, RT_WAITING_FOREVER);
    *val1 = value1;
    *val2 = value2;
    rt_mutex_release(widgit_mutex);
    }

static void widgit_entry(void *parameter)
{
    rt_kprintf("Starting Widgit!\n");

    // FillMeIn
    // Sensor thread function.
    // It should run in an infinite loop, reading sensor data
    // into the sensor component shared memory variables
    // defined at the start of the file.
    // Then it should delay for 0.5 seconds before looping.
    while(1)
        {
        rt_mutex_take(widgit_mutex, RT_WAITING_FOREVER);
        value1 = value1 - 1;
        if (value1 < 0)
            value1 = 100;
        value2 = value2 + 1;
        if (value2 > 100)
            value2 = 0;
        rt_mutex_release(widgit_mutex);
        rt_thread_mdelay(500);
        }
}

void widgit_init(void)
    {
    rt_kprintf("Starting Widgit Init!\n");

    // FillMeIn
    // The sensor needs to be initialized.
    // Create the Sensor Thread and the mutex to protect
    // the sensor shared memory area.

    widgit_tid = rt_thread_create("widgit",widgit_entry,0,2*1024,15,1);

    widgit_mutex = rt_mutex_create("wmut",RT_IPC_FLAG_PRIO);
    rt_kprintf("Finished Widgit Init!\n");
    }

void widgit_start(void)
    {
    // FillMeIn
    // The Sensor thread needs to be started.

    rt_thread_startup(widgit_tid);
    }
