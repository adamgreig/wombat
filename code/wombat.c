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

int main(void) {
    u32 counter;
    char* sentence;
    gps_data gdata;
    sentence_data sdata;

    clock_setup();
    led_peripheral_setup();
    /*adf_peripheral_setup();*/
    usart_peripheral_setup();
    gps_peripheral_setup();
    tmp_peripheral_setup();

    for(counter=0;;counter++) {
        sdata.counter = counter;
        gdata = gps_get_data();
        if(gdata.data_valid) {
            float temperature = tmp_read_temperature();
            sdata.gps = gdata;
            sdata.temperature = temperature;
            sentence = sentence_generate(sdata);
        } else {
            sentence = sentence_generate_invalid(sdata);
        }

        printf("%s\r", sentence);
        /*radio_start();*/
        /*test_radio();*/
        /*led_turn_on(LED2);*/
        /*adf_transmit_string(sentence, ADF_50_BAUD);*/
        /*adf_transmit_string(sentence, ADF_50_BAUD);*/
        /*adf_transmit_string(sentence, ADF_50_BAUD);*/
        /*led_turn_off(LED2);*/
        /*adf_turn_off();*/
    }

    return 0;
}

