/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-01-28     flybreak       first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <dfs_fs.h>
#include <dfs_littlefs_pico.h>

#include <hagl_hal.h>
#include <hagl.h>
#include <font6x9.h>

#define LED_PIN 25

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       8192
#define THREAD_TIMESLICE        5

static rt_thread_t tid1 = RT_NULL;

static void disp_thread(void *param)
{
    hagl_init();
    /* Main loop. */
    hagl_clear_screen();

    color_t fore = hagl_color(0, 0, 0);
    color_t back = hagl_color(0, 0, 255);
    color_t green = hagl_color(0, 255, 0);
    color_t black = hagl_color(0, 0, 0);

    hagl_put_scaled_text(L"Hello", 20, 100, 3.0, green, black, font6x9);

    hagl_put_scaled_text(L"Hello World!!", 0, 0, 2.0, fore, back, font6x9);
    
    hagl_flush();

    while(1)
        rt_thread_mdelay(1000);

}

/* Thread Sample */
void start_disp(void)
{
    /* Creat thread 1, Name is thread1，Entry is thread1_entry */
    tid1 = rt_thread_create("tDisp",
                            disp_thread, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    /* Start this thread if you get the thread control block */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
}

int main(void)
{
    rt_kprintf("Hello, RT-Thread!\n");

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    start_disp();

    while (1)
    {
        rt_pin_write(LED_PIN, 1);
        rt_thread_mdelay(1000);
        rt_pin_write(LED_PIN, 0);
        rt_thread_mdelay(1000);
    }
}

static int mark_times = 0;
FINSH_VAR_EXPORT(mark_times, finsh_type_int, dummy variable for finsh)

void marks_hello(int times)
{
    mark_times = times;
    rt_kprintf("Mark says hello %d times\n", times);
}

FINSH_FUNCTION_EXPORT(marks_hello , say hello from mark);
