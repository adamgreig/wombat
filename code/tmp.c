#include <libopencm3/stm32/f4/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <stdio.h>

#include "led.h"
#include "tmp.h"

void tmp_peripheral_setup(void) {

    /*i2c_peripheral_disable(I2C1);*/
    /*i2c_set_clock_frequency(I2C1, I2C_CR2_FREQ_30MHZ);*/
    /*i2c_set_standard_mode(I2C1);*/
    /*i2c_set_ccr(I2C1, 0x12F);*/
    /*i2c_set_trise(I2C1, 0x1F);*/

    /*i2c_peripheral_enable(I2C1);*/

    /*gpio_set_af(GPIOB, GPIO_AF4, GPIO6 | GPIO7);*/
    /*gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7);*/
    /*gpio_set_output_options(GPIOB,*/
            /*GPIO_OTYPE_OD, GPIO_OSPEED_2MHZ, GPIO6 | GPIO7);*/
    /*gpio_set(GPIOB, GPIO6|GPIO7);*/

    GPIOB_MODER = 0x280 | (1<<13) | (1<<15);
    GPIOB_OTYPER = (1<<6) | (1<<7);
    GPIOB_OSPEEDR = 0xC0;
    GPIOB_PUPDR = 0x100;
    GPIOB_AFRL = (4<<24) | (4<<28);
    GPIOB_AFRH = 0;

    i2c_reset(I2C1);

    I2C1_CR1 = (1<<15);
    I2C1_CR1 = 0;
    I2C1_CR2 = 30;
    /*I2C1_CCR = 0x12F;*/
    I2C1_CCR = 1600;
    I2C1_TRISE = 0x10;
    u32 reg;
    reg = I2C1_SR1;
    reg = I2C1_SR2;
    I2C1_CR1 = 1;

}

float tmp_read_temperature(void) {
    u16 temperature;
    u32 reg;

    printf("About to convert a temperature, regs are:\r\n");
    reg = I2C_CR1(I2C1);
    printf("CR1: 0x%lX, ", reg);
    reg = I2C_CR2(I2C1);
    printf("CR2: 0x%lX, ", reg);
    reg = I2C_SR1(I2C1);
    printf("SR1: 0x%lX, ", reg);
    reg = I2C_SR2(I2C1);
    printf("SR2: 0x%lX\r\n", reg);
    
    led_turn_on(3);
    
    // START, then wait for start TXd, device master, bus not busy
    /*i2c_send_start(I2C1);*/
    I2C1_CR1 = 1 | (1<<8);
    while(!(I2C1_SR1 & (1<<0)));
    /*printf("START sent OK, sending address\r\n");*/

    led_turn_on(2);

    // TMP102 with ADDR=GND address, do ACK the data, wait for address sent
    /*i2c_send_7bit_address(I2C1, 0x48, I2C_READ);*/
    reg = I2C1_SR1;
    I2C1_DR = (u8)((0x48 << 1) | 1);
    /*I2C_CR1(I2C1) |= I2C_CR1_ACK;*/
    while(!(I2C1_SR1 & (1<<1))) {
        led_turn_on(1);
        led_turn_off(1);
        led_turn_off(1);
        led_turn_off(1);
        if(I2C1_SR1 & 1<<10) {
            printf("ACK FAIL\r\n");
        }
        if(I2C1_SR1 & 1<<9) {
            printf("ARB FAIL\r\n");
        }
        if(I2C1_SR1 & 1<<8) {
            printf("BUSS ERROR\r\n");
        }
        if(I2C1_SR1 & 1<<7) {
            printf("TX EMPTY\r\n");
        }
        if(I2C1_SR1) {
            printf("SR1 NOT ZERO: 0x%lX\r\n", I2C1_SR1);
        }
    }
    /*printf("Address sent OK, reading data\r\n");*/
    reg = I2C1_SR1;
    reg = I2C1_SR2;

    led_turn_on(1);

    while(!(I2C1_SR1 & (1<<6)));

    led_turn_on(0);

    temperature = (u16)(I2C1_DR << 8);
    I2C1_CR1 = 1 | (1<<9);
    while(!(I2C1_SR1 & (1<<6)));
    temperature |= (u16)I2C1_DR;

    led_turn_off(0);
    led_turn_off(1);
    led_turn_off(2);
    led_turn_off(3);

    printf("Temperature (16bit): %X\r\n", temperature);

    return 0.0;
}
