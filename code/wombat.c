/* Wombat Central */

#include <libopencm3/stm32/f4/rcc.h>
#include <libopencm3/stm32/f4/gpio.h>

#include <stdio.h>

#include "adf7012.h"
#include "led.h"
#include "clock.h"
#include "usart.h"
#include "gps.h"

void hard_fault_handler(void);

char buffer[128];

int main(void) {
    int i = 0;
    clock_setup();
    led_peripheral_setup();
    adf_peripheral_setup();
    adf_default_config();
    usart_peripheral_setup();
    gps_peripheral_setup();

    printf("Activating GPS passthrough...\n");
    while(1) {
        /*adf_transmit_string(STRING, 27);*/
        u8 b = gps_read_byte();
        printf("%c", b);
        buffer[i] = b;
        if(i == 125) {
            i = 0;
        } else if(b == '$') {
            i = 1;
            buffer[0] = '$';
        } else if(buffer[i-2] == '*') {
            buffer[i+1] = '\n';
            buffer[i+2] = 0x00;
            printf("\r\n\r\nTransmitting current buffer: %s\r\n\r\n", buffer);
            adf_transmit_string(buffer, i+2);
            i = 0;
        } else {
            i++;
        }
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
