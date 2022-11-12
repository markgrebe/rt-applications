/*****************************************************************************
 * University of Central Missouri
 * CS4000 - Embedded Systems
 * Thermostat Project
 * 
 * Module: Temperature Sensor Driver Source
 * Author: Mark Grebe
 ****************************************************************************/

#include <stdio.h>
#include <rtthread.h>

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

 // device has default bus address of 0x76
#define ADDR 0x76

static int32_t t_fine;

static uint16_t dig_T1;
static int16_t dig_T2, dig_T3;
static uint16_t dig_P1;
static int16_t dig_P2, dig_P3, dig_P4, dig_P5;
static int16_t dig_P6, dig_P7, dig_P8, dig_P9;
static uint8_t dig_H1, dig_H3;
static int8_t dig_H6;
static int16_t dig_H2, dig_H4, dig_H5;

/* The following compensation functions are required to convert from the raw ADC
data from the chip to something usable. Each chip has a different set of
compensation parameters stored on the chip at point of manufacture, which are
read from the chip at startup and used in these routines.
*/
static int32_t compensate_temp(int32_t adc_T) {
    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t) dig_T1 << 1))) * ((int32_t) dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t) dig_T1)) * ((adc_T >> 4) - ((int32_t) dig_T1))) >> 12) * ((int32_t) dig_T3))
            >> 14;

    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

static uint32_t compensate_pressure(int32_t adc_P) {
    int32_t var1, var2;
    uint32_t p;
    var1 = (((int32_t) t_fine) >> 1) - (int32_t) 64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t) dig_P6);
    var2 = var2 + ((var1 * ((int32_t) dig_P5)) << 1);
    var2 = (var2 >> 2) + (((int32_t) dig_P4) << 16);
    var1 = (((dig_P3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) + ((((int32_t) dig_P2) * var1) >> 1)) >> 18;
    var1 = ((((32768 + var1)) * ((int32_t) dig_P1)) >> 15);
    if (var1 == 0)
        return 0;

    p = (((uint32_t) (((int32_t) 1048576) - adc_P) - (var2 >> 12))) * 3125;
    if (p < 0x80000000)
        p = (p << 1) / ((uint32_t) var1);
    else
        p = (p / (uint32_t) var1) * 2;

    var1 = (((int32_t) dig_P9) * ((int32_t) (((p >> 3) * (p >> 3)) >> 13))) >> 12;
    var2 = (((int32_t) (p >> 2)) * ((int32_t) dig_P8)) >> 13;
    p = (uint32_t) ((int32_t) p + ((var1 + var2 + dig_P7) >> 4));

    return p;
}

static uint32_t compensate_humidity(int32_t adc_H) {
    int32_t v_x1_u32r;
    v_x1_u32r = (t_fine - ((int32_t) 76800));
    v_x1_u32r = (((((adc_H << 14) - (((int32_t) dig_H4) << 20) - (((int32_t) dig_H5) * v_x1_u32r)) +
                   ((int32_t) 16384)) >> 15) * (((((((v_x1_u32r * ((int32_t) dig_H6)) >> 10) * (((v_x1_u32r *
                                                                                                  ((int32_t) dig_H3))
            >> 11) + ((int32_t) 32768))) >> 10) + ((int32_t) 2097152)) *
                                                 ((int32_t) dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t) dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);

    return (uint32_t) (v_x1_u32r >> 12);
}

// number of calibration registers to be read
#define NUM_CALIB_PARAMS 24

static void writeReg(uint8_t reg, uint8_t value)
    {
    uint8_t buf[2];

    buf[0] = reg;
    buf[1] = value;
    i2c_write_blocking(i2c0, ADDR, buf, 2, false);
    }

static void readRegs(uint8_t reg, uint8_t count, uint8_t *buffer)
    {
    i2c_write_blocking(i2c0, ADDR, &reg, 1, true);  // true to keep 
                                                    // master control 
                                                    // of bus
    // read in one go as register addresses auto-increment
    i2c_read_blocking(i2c0, ADDR, buffer, count, false);  // false, 
                                                          // we're done 
                                                          // reading
    }

/* This function reads the manufacturing assigned compensation
   parameters from the device */
static void read_compensation_parameters() {
    uint8_t buffer[NUM_CALIB_PARAMS] = { 0 };

    readRegs(0x88, NUM_CALIB_PARAMS, buffer);

    dig_T1 = buffer[0] | (buffer[1] << 8);
    dig_T2 = buffer[2] | (buffer[3] << 8);
    dig_T3 = buffer[4] | (buffer[5] << 8);

    dig_P1 = buffer[6] | (buffer[7] << 8);
    dig_P2 = buffer[8] | (buffer[9] << 8);
    dig_P3 = buffer[10] | (buffer[11] << 8);
    dig_P4 = buffer[12] | (buffer[13] << 8);
    dig_P5 = buffer[14] | (buffer[15] << 8);
    dig_P6 = buffer[16] | (buffer[17] << 8);
    dig_P7 = buffer[18] | (buffer[19] << 8);
    dig_P8 = buffer[20] | (buffer[21] << 8);
    dig_P9 = buffer[22] | (buffer[23] << 8);

    dig_H1 = buffer[25];

    readRegs(0xE1, 8, buffer);

    dig_H2 = buffer[0] | (buffer[1] << 8);
    dig_H3 = (int8_t) buffer[2];
    dig_H4 = buffer[3] << 4 | (buffer[4] & 0xf);
    dig_H5 = (buffer[5] >> 4) | (buffer[6] << 4);
    dig_H6 = (int8_t) buffer[7];
}

static void bme280_read_raw(int32_t *humidity, 
                            int32_t *pressure,
                            int32_t *temperature) {
    uint8_t buffer[8];

    readRegs(0xF7, 8, buffer);

    *pressure = ((uint32_t) buffer[0] << 12) | 
                ((uint32_t) buffer[1] << 4) | 
                (buffer[2] >> 4);
    *temperature = ((uint32_t) buffer[3] << 12) | 
                   ((uint32_t) buffer[4] << 4) |
                   (buffer[5] >> 4);
    *humidity = (uint32_t) buffer[6] << 8 | 
                buffer[7];
}

void bme280_init(i2c_inst_t *i2c, uint8_t sdaPin, uint8_t scl_pin)
    {
    rt_kprintf("In bm280_init 1!\n");
    
    // I2C is "open drain", pull ups to keep signal high when 
    // no data is being sent
    i2c_init(i2c, 100 * 1000);
    rt_kprintf("In bm280_init 2!\n");
    gpio_set_function(sdaPin, GPIO_FUNC_I2C);
    rt_kprintf("In bm280_init 3!\n");
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    rt_kprintf("In bm280_init 4!\n");
    gpio_pull_up(sdaPin);
    rt_kprintf("In bm280_init 5!\n");
    gpio_pull_up(scl_pin);

    rt_kprintf("In bm280_init 6!\n");
    read_compensation_parameters();

    rt_kprintf("In bm280_init 7!\n");
    // Humidity oversampling register - going for x1
    writeReg(0xF2,0x1);
    rt_kprintf("In bm280_init 8!\n");
    // Set rest of oversampling modes and run mode to normal
    writeReg(0xF4,0x27);
    rt_kprintf("In bm280_init 9!\n");
    }

uint8_t bme280_read_chipid()
    {
    uint8_t id;
    readRegs(0xD0, 1, &id);
    return(id);
    }

void bme280_read_data(float *temperature, float *humidity, uint32_t *pressure)
    {
    int32_t humid, press, temp;

    bme280_read_raw(&humid, &press, &temp);

    // These are the raw numbers from the chip, so we need to run through the
    // compensations to get human understandable numbers
    press = compensate_pressure(press);
    temp = compensate_temp(temp);
    humid = compensate_humidity(humid);

    if (temperature != NULL)
        *temperature = temp / 100.0;
    if (humidity != NULL)
        *humidity = humid / 1024.0;
    if (pressure != NULL)
        *pressure = press;
    }
