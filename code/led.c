#include <libopencm3/stm32/f4/gpio.h>
#include "led.h"

void led_set_pin_output(u32 prt, u16 pin) {
    gpio_mode_setup(prt, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin);
}

void led_peripheral_setup() {
    led_set_pin_output(GPIOC, GPIO0);
    led_set_pin_output(GPIOC, GPIO1);
    led_set_pin_output(GPIOC, GPIO2);
    led_set_pin_output(GPIOC, GPIO3);
}

void led_wait() {
    u32 i;
    for(i=0; i<800000; i++)
        __asm__("nop");
}

void led_dance() {
    GPIOC_ODR = 0;
    led_wait();
    GPIOC_ODR = GPIO0;
    led_wait();
    GPIOC_ODR = GPIO0 | GPIO1;
    led_wait();
    GPIOC_ODR = GPIO0 | GPIO1 | GPIO2;
    led_wait();
    GPIOC_ODR = GPIO0 | GPIO1 | GPIO2 | GPIO3;
    led_wait();
    GPIOC_ODR = GPIO1 | GPIO2 | GPIO3;
    led_wait();
    GPIOC_ODR = GPIO2 | GPIO3;
    led_wait();
    GPIOC_ODR = GPIO3;
    led_wait();
    GPIOC_ODR = 0;
}

void led_turn_on(u8 led) {
    gpio_set(GPIOC, 1<<led);
}

void led_turn_off(u8 led) {
    gpio_clear(GPIOC, 1<<led);
}
