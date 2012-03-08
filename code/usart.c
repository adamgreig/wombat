#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/f4/gpio.h>

#include <errno.h>
#include <stdio.h>

#include "usart.h"

void usart_peripheral_setup(void) {
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO9);

    usart_set_baudrate(USART1, 38400);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_mode(USART1, USART_MODE_TX);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

    usart_enable(USART1);
}

int _write(int file, char *ptr, int len) {
    int i;

    if(file == 1) {
        for(i=0; i<len; i++) {
            usart_send_blocking(USART1, ptr[i]);
        }
        return i;
    }

    errno = EIO;
    return -1;
}
