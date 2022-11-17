/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Widget Project
 * 
 * Module: GUI Component Source
 * Author:
 ****************************************************************************/

#include <rtthread.h>
#include <hagl_hal.h>
#include <hagl.h>
#include <font6x9.h>
#include <pico/stdlib.h>
#include <math.h>
#include <wchar.h>
#include "compare.h"
#include "widget.h"
#include "gui.h"

// GUI Thread ID
static rt_thread_t gui_tid = RT_NULL;

// Note, the hagl display library uses "Wide" characters
// which are able to handle unicode characters.
// Therefore, you can use printf and sprintf, but
// have to use wprintf and swprintf to print wide characters
// Also, in C to convert a Floating point value to an 
// float to an integer you use the round() function.
// For example, the following will take the float value temp
// and write the 2 digit temperature into the wide string 
// array temp_buff. (Which can then be passed to a hagl
// function to display)
//
//    float temp
//    int disp_temp;
//    wchar_t temp_buff[5];
//
//    disp_temp = round(temp);
//    swprintf(temp_buff,5,L"%02d",disp_temp);
//

static void gui_entry(void *parameter)
    {
    rt_kprintf("Starting GUI!\n");
    int val1;
    int val2;
    wchar_t val1_buff[5];
    wchar_t val2_buff[5];
    color_t white = hagl_color(255, 255, 255);
    color_t black = hagl_color(0, 0, 0);


    // FillMeIn
    // GUI thread function.
    while (1)
        {
        char msg[10];
        rt_err_t status;

        widgit_read_vals(&val1, &val2);
    
        swprintf(val1_buff,5,L"%03d",val1);
        hagl_put_scaled_text(val1_buff,0,0,5.0,white,black,font6x9);

        swprintf(val2_buff,5,L"%03d",val2);
        hagl_put_scaled_text(val2_buff,0,100,5.0,white,black,font6x9);

        status = rt_mq_recv(compare_msgq, msg, 10, 0);
        if (status == RT_EOK)
            {
            hagl_put_scaled_text(L"Equal",0,150,5.0,black,white,font6x9);
            }
        else
            {
            hagl_put_scaled_text(L"     ",0,150,5.0,white,black,font6x9);
            }

        hagl_flush();
        rt_thread_mdelay(100);
        }
    }

void gui_init(void)
    {
    rt_kprintf("Starting GUI Init!\n");

    // FillMeIn
    // The GUI component needs to be initialized.
    // Create the GUI Thread and initialize the display.
    gui_tid = rt_thread_create("gui",gui_entry,0,32*1024,16,1);
    rt_kprintf("Gui_tid=%x\n",gui_tid);

    hagl_init();
    hagl_clear_screen();
    hagl_flush();
    rt_kprintf("Finished GUI Init!\n");
    }

void gui_start(void)
    {
    // FillMeIn
    // The GUI thread needs to be started.
    rt_thread_startup(gui_tid);
    }
