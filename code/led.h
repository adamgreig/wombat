#ifndef WOMBAT_LED_H
#define WOMBAT_LED_H

void led_peripheral_setup(void);
void led_turn_on(uint8_t leds);
void led_turn_off(uint8_t leds);

void led_quickflash_outer(void);
void led_quickflash_inner(void);
void led_flash_outer(void);
void led_flash_inner(void);

void led_quickflash(uint8_t leds);
void led_flash(uint8_t leds);

#define LED1 GPIO3
#define LED2 GPIO2
#define LED3 GPIO1
#define LED4 GPIO0

#endif
