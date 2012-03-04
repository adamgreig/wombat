/*
 * ADF7012 stuff
 */

#include <libopencm3/stm32/f4/gpio.h>

#include "adf7012.h"

void adf_set_pin_output(u32 prt, u16 pin) {
    gpio_mode_setup(prt, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin);
}

void adf_peripheral_setup() {
    adf_set_pin_output(ADF_CLK_PORT, ADF_CLK);
    adf_set_pin_output(ADF_DATA_PORT, ADF_DATA);

    adf_set_pin_output(ADF_CE_PORT, ADF_CE);
    adf_set_pin_output(ADF_LE_PORT, ADF_LE);
    adf_set_pin_output(ADF_TXCLK_PORT, ADF_TXCLK);
    adf_set_pin_output(ADF_TXDATA_PORT, ADF_TXDATA);
    adf_set_pin_output(ADF_MUXOUT_PORT, ADF_MUXOUT);
    adf_set_pin_output(ADF_CLKOUT_PORT, ADF_CLKOUT);

}

void adf_wait(u32 count) {
    u32 i;
    for(i=0; i<count; i++)
        __asm__("nop");
}

void adf_wait_ms(u8 ms) {
    adf_wait(ms * ADF_1_MS);
}


void adf_default_config() {
    adf_reset();

    /* Register 0 */
    adf_write_reg(
        (0<<ADF_C1) | (0<<ADF_C2) |
        (0<<ADF_R0_R1) | (1<<ADF_R0_R2) | (0<<ADF_R0_R3) | (0<<ADF_R0_R4) |
        (1<<ADF_R0_CL1) | (1<<ADF_R0_CL2) | (1<<ADF_R0_CL3) | (1<<ADF_R0_CL4)
    );

    /* Register 1 */
    adf_write_reg(
        (1<<ADF_C1) | (0<<ADF_C2) |
        (1<<ADF_R1_M1) | (1<<ADF_R1_M3) | (1<<ADF_R1_M4) | (1<<ADF_R1_M7) |
        (1<<ADF_R1_M8) | (1<<ADF_R1_M11) | (1<<ADF_R1_M12) |
        (1<<ADF_R1_N5) | (1<<ADF_R1_N6) | (1<<ADF_R1_N8)
    );

    /* Register 2 */
    adf_write_reg(
        (0<<ADF_C1) | (1<<ADF_C2) |
        (1<<ADF_R2_P1) | (1<<ADF_R2_P2) | (1<<ADF_R2_P3) | (1<<ADF_R2_P4) |
        (1<<ADF_R2_P5) |
        (1<<ADF_R2_D1)
    );

    /* Register 3 */
    adf_write_reg(
        (1<<ADF_C1) | (1<<ADF_C2) |
        (1<<ADF_R3_PD1) | (0<<ADF_R3_PD2) | (1<<ADF_R3_PD3) |
        (1<<ADF_R3_CP1) | (1<<ADF_R3_CP2) |
        (0<<ADF_R3_M1) | (0<<ADF_R3_M2) | (1<<ADF_R3_M3) | (0<<ADF_R3_M4) |
        (1<<ADF_R3_LD1) |
        (0<<ADF_R3_VB1) | (1<<ADF_R3_VB2) | (1<<ADF_R3_VB3) | (0<<ADF_R3_VB4) |
        (1<<ADF_R3_PA1) | (1<<ADF_R3_PA2) | (1<<ADF_R3_PA3)
    );

    adf_wait_ms(100);

    /* Register 3, PA on */
    adf_write_reg(
        (1<<ADF_C1) | (1<<ADF_C2) |
        (1<<ADF_R3_PD1) | (1<<ADF_R3_PD2) | (1<<ADF_R3_PD3) |
        (1<<ADF_R3_CP1) | (1<<ADF_R3_CP2) |
        (0<<ADF_R3_M1) | (0<<ADF_R3_M2) | (1<<ADF_R3_M3) | (0<<ADF_R3_M4) |
        (1<<ADF_R3_LD1) |
        (0<<ADF_R3_VB1) | (1<<ADF_R3_VB2) | (1<<ADF_R3_VB3) | (0<<ADF_R3_VB4) |
        (1<<ADF_R3_PA1) | (1<<ADF_R3_PA2) | (1<<ADF_R3_PA3)
    );

}

void adf_reset() {
    gpio_clear(ADF_CE_PORT, ADF_CE);
    gpio_set(ADF_LE_PORT, ADF_LE);
    gpio_set(ADF_TXDATA_PORT, ADF_TXDATA);
    gpio_set(ADF_CLK_PORT, ADF_CLK);
    gpio_set(ADF_DATA_PORT, ADF_DATA);
    adf_wait_ms(100);
    gpio_set(ADF_CE_PORT, ADF_CE);
    adf_wait_ms(100);
}

void adf_write_reg(u32 data) {
    s8 i;

    gpio_clear(ADF_LE_PORT, ADF_LE);
    adf_wait_ms(2);
    for(i=31; i>=0; i--) {
        if((data & (1<<i))>>i)
            gpio_set(ADF_DATA_PORT, ADF_DATA);
        else
            gpio_clear(ADF_DATA_PORT, ADF_DATA);
        adf_wait_ms(2);
        gpio_set(ADF_CLK_PORT, ADF_CLK);
        adf_wait_ms(2);
        gpio_clear(ADF_CLK_PORT, ADF_CLK);
        adf_wait_ms(2);
    }
    gpio_set(ADF_LE_PORT, ADF_LE);
    adf_wait_ms(2);
}

void adf_transmit_bit(u8 bit) {
    if(bit)
        gpio_set(ADF_TXDATA_PORT, ADF_TXDATA);
    else
        gpio_clear(ADF_TXDATA_PORT, ADF_TXDATA);
}

void adf_transmit_byte(u8 byte) {
    s8 i;

    /* START */
    adf_transmit_bit(0);
    adf_wait(ADF_300_BAUD);

    /* DATA */
    for(i=0; i<8; i++) {
        if(byte & 1<<i)
            adf_transmit_bit(1);
        else
            adf_transmit_bit(0);
        adf_wait(ADF_300_BAUD);
    }

    /* STOP */
    adf_transmit_bit(1);
    adf_wait(ADF_300_BAUD);
    adf_wait(ADF_300_BAUD);
}

void adf_transmit_string(char* data, u32 length) {
    u32 i;

    for(i=0; i<length; i++)
        adf_transmit_byte(data[i]);
}

