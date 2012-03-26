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

void radio_start(void) {
    led_turn_on(LED1);

    adf_reset_config();

    printf("Setting radio to 434.000MHz...\r\n");
    u16 m = 2437;
    adf_set_n(176); adf_set_m(m);
    adf_set_muxout(ADF_MUXOUT_DIGITAL_LOCK);
    adf_set_vco_adjust(3);
    adf_set_vco_bias(8);
    adf_write_config();

    adf_set_pll_enable(ADF_ON);
    adf_write_config();

    printf("Waiting for radio lock...\r\n");

    u32 n;
    while(!adf_locked()) {
        delay_ms(1);
        n++;
        if(n > 1000) {
            // oh no, 1 second and no lock?
            led_turn_on(LED2);
            m -= 100;
            if(m < 900) {
                //meh
                m = 2437;
            }
            adf_set_m(m);
            adf_write_config();
            n = 0;
            led_turn_off(LED2);
        }
    }

    printf("Radio locked, enabling PA...\r\n");
    adf_set_pa_enable(ADF_ON);
    adf_set_pa_level(58);
    adf_write_config();

    printf("Radio ready to go!\r\n");

    led_turn_off(LED1);

}

void find_radio_freq(void) {
    printf("Beginning search for lockable frequency...\r\n");
    adf_reset_config();

    u8 n = 170;
    u16 m = 0;

    adf_set_n(n); adf_set_m(m);
    adf_set_muxout(ADF_MUXOUT_DIGITAL_LOCK);
    adf_set_vco_adjust(1);
    adf_set_vco_bias(6);
    adf_write_config();

    adf_set_pll_enable(ADF_ON);
    adf_write_config();

    /*for(n = 174; n < 185; n++) {*/
        /*for(m = 0; m < 4000; m += 100) {*/
    for(n = 178; n > 170; n--) {
        for(m = 4096; m > 100; m -= 100) {
            printf("N=%u M=%u\r\n", n, m);
            adf_set_n(n); adf_set_m(m);
            adf_write_config();
            delay_ms(50);
            if(adf_locked()) {
                float freq = (4.9152 / 2.0) * ((float)n + ((float)m / 4096.0));
                printf("Locked! f = %.3fMHz\r\n", freq);
                for(;;);
            }
        }
    }
}

void test_radio(void) {
    setbuf(stdout, NULL);

    printf("Starting to run radio test...\r\n\r\n");

    printf("Resetting radio...                   ");
    adf_reset_config();
    printf("OK\r\n");

    printf("Testing MUXOUT=HIGH...               ");
    adf_set_muxout(ADF_MUXOUT_LOGIC_HIGH);
    adf_write_config();

    if(adf_locked()) {
        printf("OK\r\n");
    } else {
        printf("FAIL\r\n");
    }

    printf("Locking to 434MHz...                 ");
    u8 adj = 1;
    u8 bias = 1;

    adf_set_muxout(ADF_MUXOUT_DIGITAL_LOCK);
    adf_set_n(176);
    adf_set_m(2437);
    adf_set_pll_enable(ADF_ON);
    adf_set_vco_adjust(adj);
    adf_set_vco_bias(bias);
    adf_write_config();
    delay_ms(50);

    while(!adf_locked()) {
        adf_set_vco_adjust(adj);
        adf_set_vco_bias(bias);
        adf_write_config();
        delay_ms(50);
        bias += 1;
        if(bias == 14) {
            adj += 1;
            bias = 1;
        }
        if(adj == 4) {
            printf("FAIL\r\n    Could not find lock -- aborting.\r\n");
            for(;;);
        }
    }
    printf("OK\r\n    Locked at ADJUST=%u, BIAS=%u\r\n", adj, bias);

    printf("Turning on PA and returning control. ");
    /*printf("Turning on PA and transmitting...    ");*/
    adf_set_pa_enable(ADF_ON);
    adf_set_pa_level(30);
    adf_write_config();

    /*char str[10] = "WOMBAT\r\n";*/
    /*while(1)*/
        /*adf_transmit_string(str, ADF_50_BAUD);*/

    /*printf("Tests over, stopping.\r\n");*/
    /*for(;;);*/

}

u16 crc_update(u16 crc, u8 data) {
    int i;

    crc = crc ^ ((u16)data << 8);
    for (i=0; i<8; i++)
    {
        if (crc & 0x8000)
            crc = (crc << 1) ^ 0x1021;
        else
            crc <<= 1;
    }

    return crc;
}

int main(void) {
    clock_setup();
    led_peripheral_setup();
    /*adf_peripheral_setup();*/
    usart_peripheral_setup();
    gps_peripheral_setup();
    tmp_peripheral_setup();

    /*test_radio();*/
    /*find_radio_freq();*/

    u32 counter;
    for(counter=0;;counter++) {
        char pre_sentence[256 - 10];
        char sentence[256];
        u16 crc = 0xFFFF;
        u8 i;

        gps_data data = gps_get_data();
        if(data.data_valid) {
            float temperature = tmp_read_temperature();
            sprintf(pre_sentence,
                    "WOMBAT,%lu,%02u:%02u:%02u,%.5f,%.5f,%li,%.0f",
                    counter, data.hour, data.minute, data.second,
                    data.latitude, data.longitude, data.altitude, temperature);
        } else {
            sprintf(pre_sentence, "WOMBAT,%lu,INVALID GPS DATA", counter);
        }

        for(i=0; i<strlen(pre_sentence); i++) {
            crc = crc_update(crc, pre_sentence[i]);
        }
        sprintf(sentence, "$$$$$$%s*%04X\n", pre_sentence, crc);
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

