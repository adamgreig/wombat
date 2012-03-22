#include <libopencm3/stm32/f4/gpio.h>

#include "delay.h"
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

void led_turn_on(u8 leds) {
    gpio_set(GPIOC, leds);
}

void led_turn_off(u8 leds) {
    gpio_clear(GPIOC, leds);
}
