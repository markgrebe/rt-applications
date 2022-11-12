/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Thermostat Project
 * 
 * Module: Input Component Source
 * Author:
 ****************************************************************************/

#include <rtthread.h>
#include <pico/stdlib.h>
#include "input.h"
#include "control.h"

#define NUM_BUTTONS (4)
// Array containing the button pin numbers
static uint8_t buttton_pins[NUM_BUTTONS] = {12,13,14,15};
// Array to send character messages for a button press
static char msg[NUM_BUTTONS] = {'A','B','X','Y'};

// Debounce control
static uint32_t time[NUM_BUTTONS];
static const uint32_t delayTime = 200; // Delay for every push button may vary

static void button_int_handler(uint gpio, uint32_t events)
    {
    uint8_t i;

    rt_interrupt_enter();
    for (i=0;i<NUM_BUTTONS;i++)
        {
        if (gpio == buttton_pins[i])
            {
            uint32_t currTime;

            currTime = to_ms_since_boot(get_absolute_time());
            if ((currTime-time[i])>delayTime) 
                {
                time[i] = to_ms_since_boot(get_absolute_time());

                // FillMeIn
                // Send a character message to the control_msgq
                // The message should contain the key that was
                // pressed

                rt_mq_send(control_msgq,&msg[i],1);

                rt_interrupt_leave();
                return;
                }
            }
        }

    rt_interrupt_leave();
    }

void input_init(void)
    {
    uint8_t i;

    for (i=0; i<NUM_BUTTONS; i++)
        {
        gpio_init(buttton_pins[i]);
        gpio_set_dir(buttton_pins[i], GPIO_IN);
        gpio_set_pulls(buttton_pins[i], true, false);
        if (i==0)
            gpio_set_irq_enabled_with_callback(buttton_pins[i], 
                                               GPIO_IRQ_EDGE_FALL, 
                                               true, 
                                               button_int_handler);
        else
            gpio_set_irq_enabled(buttton_pins[i], 
                                 GPIO_IRQ_EDGE_RISE, 
                                 true);
        gpio_set_inover(buttton_pins[i], GPIO_OVERRIDE_INVERT);
        time[i] = to_ms_since_boot(get_absolute_time());
        }
    }
