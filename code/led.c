#include <libopencm3/stm32/f4/gpio.h>

#include "delay.h"
#include "led.h"

void led_set_pin_output(uint32_t prt, uint16_t pin);

void led_set_pin_output(uint32_t prt, uint16_t pin) {
    gpio_mode_setup(prt, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin);
}

void led_peripheral_setup() {
    led_set_pin_output(GPIOC, GPIO0);
    led_set_pin_output(GPIOC, GPIO1);
    led_set_pin_output(GPIOC, GPIO2);
    led_set_pin_output(GPIOC, GPIO3);
}

void led_turn_on(uint8_t leds) {
    gpio_set(GPIOC, leds & 15);
}

void led_turn_off(uint8_t leds) {
    gpio_clear(GPIOC, leds & 15);
}

void led_quickflash_outer(void) {
    led_turn_off(LED2|LED3);
    led_turn_on(LED1|LED4);
    delay_ms(1);
    led_turn_off(LED1|LED4);
}

void led_quickflash_inner(void) {
    led_turn_off(LED1|LED4);
    led_turn_on(LED2|LED3);
    delay_ms(1);
    led_turn_off(LED2|LED3);
}

void led_flash_outer(void) {
    led_turn_off(LED2|LED3);
    led_turn_on(LED1|LED4);
    delay_ms(100);
    led_turn_off(LED1|LED4);
    delay_ms(100);
    led_turn_on(LED1|LED4);
    delay_ms(100);
    led_turn_off(LED1|LED4);
}

void led_flash_inner(void) {
    led_turn_off(LED1|LED4);
    led_turn_on(LED2|LED3);
    delay_ms(100);
    led_turn_off(LED2|LED3);
    delay_ms(100);
    led_turn_on(LED2|LED3);
    delay_ms(100);
    led_turn_off(LED2|LED3);
}

void led_quickflash(uint8_t leds) {
    led_turn_off(~leds);
    led_turn_on(leds);
    delay_ms(1);
    led_turn_off(leds);
}

void led_flash(uint8_t leds) {
    led_turn_off(~leds);
    led_turn_on(leds);
    delay_ms(100);
    led_turn_off(leds);
    delay_ms(100);
    led_turn_on(leds);
    delay_ms(100);
    led_turn_off(leds);
}
