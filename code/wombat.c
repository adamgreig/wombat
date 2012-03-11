/* Wombat Central */

#include <libopencm3/stm32/f4/rcc.h>
#include <libopencm3/stm32/f4/gpio.h>

#include <stdio.h>

#include "adf.h"
#include "led.h"
#include "clock.h"
#include "usart.h"
#include "gps.h"
#include "delay.h"

char buffer[128];

int main(void) {
    clock_setup();
    led_peripheral_setup();
    adf_peripheral_setup();
    usart_peripheral_setup();
    gps_peripheral_setup();
    
    adf_reset_config();

    printf("Setting to 434.000MHz...\r\n");
    adf_set_n(176); adf_set_m(2437);
    adf_set_muxout(ADF_MUXOUT_DIGITAL_LOCK);
    adf_set_vco_adjust(3);
    adf_set_vco_bias(9);
    adf_write_config();

    adf_set_pll_enable(ADF_ON);
    adf_write_config();

    printf("Waiting for lock...\r\n");

    while(!adf_locked());

    printf("Locked, enabling PA...\r\n");
    adf_set_pa_enable(ADF_ON);
    adf_set_pa_level(15);
    adf_write_config();

    printf("Go time!\r\n");

    char buf[128];
    sprintf(buf, "UU HELLO WORLD UU\r\n");
    for(;;)
        adf_transmit_string(buf, 18, ADF_50_BAUD);

    return 0;
}

