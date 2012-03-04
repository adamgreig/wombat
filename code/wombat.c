/* Wombat Central */

#include <libopencm3/stm32/f4/rcc.h>
#include <libopencm3/stm32/f4/gpio.h>

#include "adf7012.h"
#include "led.h"

void clock_setup(void) {
    rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_120MHZ]);
    rcc_peripheral_enable_clock(&RCC_AHB1ENR, RCC_AHB1ENR_IOPAEN);
    rcc_peripheral_enable_clock(&RCC_AHB1ENR, RCC_AHB1ENR_IOPBEN);
    rcc_peripheral_enable_clock(&RCC_AHB1ENR, RCC_AHB1ENR_IOPCEN);
}

void hard_fault_handler(void);

int main(void) {
    clock_setup();
    /*adf_peripheral_setup();*/
    /*adf_default_config();*/
    led_peripheral_setup();

    while(1) {
        /*adf_transmit_string(STRING, 27);*/
        led_dance();
    }

    return 0;
}

void hard_fault_handler(void) {
    int i;
    RCC_AHB1ENR     |= (1<<2);
    GPIOC_MODER      = (1<<0) | (1<<2) | (1<<4) | (1<<6);
    while(1) {
        GPIOC_ODR        = (1<<3) | (1<<2) | (1<<1) | (1<<0);
        for(i=0; i<200000; i++)
            __asm__("nop");
        GPIOC_ODR        = 0;
        for(i=0; i<200000; i++)
            __asm__("nop");
    }
}
