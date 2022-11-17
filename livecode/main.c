/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Widget Project
 * 
 * Module: Main Source
 * Author:
 ****************************************************************************/

#include <rtthread.h>
#include <rtdevice.h>
#include "gui.h"
#include "widget.h"
#include "compare.h"

int main(void)
{
    rt_kprintf("Hello, Widget User!\n");

    // Initialize each of the components.
    gui_init();
    widgit_init();
    compare_init();

    // Start the components with threads.
    widgit_start();
    compare_start();
    gui_start();

    while (1)
        {
        rt_thread_mdelay(1000);
        }
}

