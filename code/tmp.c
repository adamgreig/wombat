#include <libopencm3/stm32/f4/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <stdio.h>

#include "led.h"
#include "tmp.h"

void tmp_peripheral_setup(void) {

    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7);
    gpio_set_output_options(GPIOB,
            GPIO_OTYPE_OD, GPIO_OSPEED_2MHZ, GPIO6 | GPIO7);

    // Set this manually due to a big in libopencm3
    /*gpio_set_af(GPIOB, GPIO_AF4, GPIO6 | GPIO7);*/
    GPIOB_AFRL = (4<<(6*4)) | (4<<(7*4));

    i2c_reset(I2C1);

    i2c_peripheral_disable(I2C1);
    i2c_set_clock_frequency(I2C1, I2C_CR2_FREQ_30MHZ);
    i2c_set_standard_mode(I2C1);
    i2c_set_ccr(I2C1, 1600);
    i2c_set_trise(I2C1, 0x10);

    i2c_peripheral_enable(I2C1);

}

float tmp_read_temperature(void) {
    // Store signed temperature info (12 bit from device, with 4LSBs = 0)
    s16 temperature;
    // Dummy variable to store read results from registers that must be read
    u32 reg;

    // Send START
    i2c_send_start(I2C1);
    while(!(I2C1_SR1 & I2C_SR1_SB));

    // Send the TMP102's address and READ
    i2c_send_7bit_address(I2C1, 0x48, I2C_READ);
    while(!(I2C1_SR1 & I2C_SR1_ADDR));

    // Clear ADDR bit, send ACKs, read byte one (MSB)
    reg = I2C1_SR2;
    I2C1_CR1 |= I2C_CR1_ACK;
    while(!(I2C1_SR1 & I2C_SR1_BTF));
    temperature = (u16)(I2C1_DR << 8);

    // Stop sending ACKs, send STOP, read byte two (LSB)
    I2C1_CR1 &= ~I2C_CR1_ACK;
    I2C1_CR1 |= I2C_CR1_STOP;
    while(!(I2C1_SR1 & I2C_SR1_BTF));
    temperature |= I2C1_DR;

    temperature >>= 4;

    printf("Temperature: %.2f\xC2\xB0""C\r\n", (float)temperature * 0.0625);

    return (float)temperature * 0.0625;
}

