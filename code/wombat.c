/* Wombat Central */

#include <libopencm3/stm32/f4/rcc.h>
#include <libopencm3/stm32/f4/gpio.h>

#include <stdio.h>
#include <string.h>

#include "adf.h"
#include "led.h"
#include "clock.h"
#include "usart.h"
#include "gps.h"
#include "delay.h"
#include "tmp.h"
#include "sentence.h"
#include "watchdog.h"


int main(void) {
    uint32_t counter;
    char* sentence;
    gps_data gdata;
    sentence_data sdata;

    watchdog_setup();

    clock_setup();
    led_peripheral_setup();
    adf_peripheral_setup();
    usart_peripheral_setup();
    gps_peripheral_setup();
    tmp_peripheral_setup();

    setbuf(stdout, NULL);

    printf("\r\n\r\n");
    printf("************************************************************\r\n");
    printf("*                   WOMBAT IS STARTING UP                  *\r\n");
    printf("************************************************************\r\n");
    printf("\r\n\r\n");

    printf("Configuring radio... ");
    adf_setup();
    printf("done, locking... ");
    if(!adf_lock()) {
        printf("FAIL, stopping.\r\n");
        for(;;)
            led_flash_outer();
    }
    printf("locked, turning on... ");
    adf_power_on();
    printf("done.\r\n");

    adf_transmit_string("\n\n*** WOMBAT INITIALISING ***\n\n", ADF_300_BAUD);

    adf_power_off();

    led_flash_outer();
    led_flash_inner();

    for(counter=0;;counter++) {
        watchdog_reset();

        sdata.counter = counter;
        gdata = gps_get_data();
        if(gdata.data_valid) {
            printf("Got valid GPS data... ");
            if(gdata.lock_valid) {
                printf("GPS locked.\r\n");
                led_quickflash_inner();

                printf("Getting temperature... ");
                float temperature = tmp_read_temperature();
                printf("done.\r\n");

                sdata.gps = gdata;
                sdata.temperature = temperature;
                sentence = sentence_generate(sdata);
            } else {
                printf("no GPS lock.\r\n");
                led_quickflash_outer();
                sentence = sentence_generate_no_lock(sdata);
            }
        } else {
            printf("Invalid GPS data.\r\n");
            led_quickflash_outer();
            led_quickflash_outer();
            led_quickflash_outer();
            sentence = sentence_generate_invalid(sdata);
        }

        printf("Current sentence: %s\r", sentence);

        adf_power_on();

        if(counter % 3) {
            printf("Transmitting at 50 baud once... ");
            adf_transmit_string(sentence, ADF_50_BAUD);
            printf("done.\r\n\r\n");
        } else {
            printf("Transmitting at 300 baud five times... ");
            adf_transmit_string(sentence, ADF_300_BAUD);
            adf_transmit_string(sentence, ADF_300_BAUD);
            adf_transmit_string(sentence, ADF_300_BAUD);
            adf_transmit_string(sentence, ADF_300_BAUD);
            adf_transmit_string(sentence, ADF_300_BAUD);
            printf("done.\r\n\r\n");
        }

        if(counter % 10) {
            printf("Re-locking VCO after ten sentences... ");
            if(!adf_lock()) {
                printf("FAIL, stopping.\r\n");
                for(;;)
                    led_flash_outer();
            }
            printf("done.\r\n");
        }

        adf_power_off();
    }

    return 0;
}

