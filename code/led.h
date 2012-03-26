#ifndef WOMBAT_LED_H
#define WOMBAT_LED_H

void led_peripheral_setup(void);
void led_turn_on(u8 leds);
void led_turn_off(u8 leds);

void led_quickflash_outer(void);
void led_quickflash_inner(void);
void led_flash_outer(void);
void led_flash_inner(void);

void led_quickflash(u8 leds);
void led_flash(u8 leds);

#define LED1 GPIO3
#define LED2 GPIO2
#define LED3 GPIO1
#define LED4 GPIO0

#endif
