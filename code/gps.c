#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/f4/gpio.h>

#include "gps.h"

void gps_peripheral_setup(void) {
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO3);

    usart_set_baudrate(USART2, 38400);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_mode(USART2, USART_MODE_TX_RX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

    usart_enable(USART2);
}

u8 gps_read_byte(void) {
    u16 b = usart_recv_blocking(USART2);
    return (u8)(b & 0xFF);
}
