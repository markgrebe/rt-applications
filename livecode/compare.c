/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Widget Project
 * 
 * Module: Compare Component Source
 * Author:
 ****************************************************************************/
#include <rtthread.h>
#include "widget.h"
#include "compare.h"

#define TEMP_DELTA                      (0.5)

// Control Thread ID
static rt_thread_t compare_tid = RT_NULL;

// Control Thread Message Queue
rt_mq_t compare_msgq;


static void compare_entry(void *parameter)
{
    rt_kprintf("Starting Compare!\n");
    int val1;
    int val2;
    int equal;

    // FillMeIn
    // Control thread function.
    while(1)
        {
        widgit_read_vals(&val1, &val2);
        equal = (val1 == val2);

        if (equal)
            {
            rt_kprintf("Sending\n");
            rt_mq_send(compare_msgq, "Equal", 5);
            }
        rt_thread_mdelay(500);
        }

}

void compare_init(void)
    {
    rt_kprintf("Starting Compare Init!\n");

    // FillMeIn
    // The Control component needs to be initialized.
    // Create the Control Thread, the mutex to protect
    // the Control shared memory area, and the
    // Control message queue for key input.
    compare_tid = rt_thread_create("compare",compare_entry,0,2*1024,17,1);

    compare_msgq = rt_mq_create("cq", 10, 10, RT_IPC_FLAG_PRIO);

    }

void compare_start(void)
    {
    // FillMeIn
    // The Control thread needs to be started.
    rt_thread_startup(compare_tid);
    }
