/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Thermostat Project
 * 
 * Module: Control Component Header
 * Author:
 ****************************************************************************/

#define CONTROL_MSGQ_SIZE       (sizeof(char))
#define CONTROL_MSGQ_LEN        (10)

typedef enum 
    {
    COOL,
    HEAT,
    AUTO
    } HVACMode;

extern rt_mq_t control_msgq;

void control_init(void);
void control_start(void);

float control_get_cool_temperature(void);
float control_get_heat_temperature(void);
void control_get_status(HVACMode *mode,
                        int *cool_status,
                        int *heat_status,
                        int *fan_status);

