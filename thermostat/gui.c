/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Thermostat Project
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
#include "control.h"
#include "sensor.h"
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

    // FillMeIn
    // GUI thread function.
    // It should run in an infinite loop, displaying the
    // current temperature, current set temperature,
    // and current heater, AC, and fan status.
    // Then it should delay for 0.5 seconds before looping.

    }

void gui_init(void)
    {
    rt_kprintf("Starting GUI Init!\n");

    // FillMeIn
    // The GUI component needs to be initialized.
    // Create the GUI Thread and initialize the display.

    rt_kprintf("Finished GUI Init!\n");
    }

void gui_start(void)
    {
    // FillMeIn
    // The GUI thread needs to be started.

    }
