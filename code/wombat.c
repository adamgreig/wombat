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

void radio_start(void) {
    led_turn_on(0);

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
            led_turn_on(3);
            m -= 100;
            if(m < 900) {
                //meh
                m = 2437;
            }
            adf_set_m(m);
            adf_write_config();
            n = 0;
            led_turn_off(3);
        }
    }

    printf("Radio locked, enabling PA...\r\n");
    adf_set_pa_enable(ADF_ON);
    adf_set_pa_level(58);
    adf_write_config();

    printf("Radio ready to go!\r\n");

    led_turn_off(0);

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
    adf_peripheral_setup();
    usart_peripheral_setup();
    gps_peripheral_setup();

    test_radio();
    /*find_radio_freq();*/

    u32 counter;
    for(counter=0;;counter++) {
        s32 altitude = 0;
        double latitude = 0.0, longitude = 0.0;
        u8 hour = 0, minute = 0, second = 0;

        /*gps_get_position(&lat, &lon, &alt, &hr, &min, &sec);*/
        char buf[36];
        u8 b, i;
        for(i=0; i<36; i++) {
            b = gps_read_byte();
            if(i == 0 && b != 0xB5) {
                i = 255;
                continue;
            }
            buf[i] = b;
        }

        if(buf[0] != 0xB5 || buf[1] != 0x62) {
            printf("Received packet with bad sync bits 0x%x%x, skipping.\r\n",
                    buf[0], buf[1]);
            continue;
        }
        if(buf[2] != 0x01 || buf[3] != 0x02) {
            printf("Received packet with unexpected ID 0x%x%x, skipping.\r\n",
                    buf[2], buf[3]);
            continue;
        }

        u32 time = (buf[6]  | buf[7]<<8  | buf[8]<<16  | buf[9]<<24);
        s32 lon  = (buf[10] | buf[11]<<8 | buf[12]<<16 | buf[13]<<24);
        s32 lat  = (buf[14] | buf[15]<<8 | buf[16]<<16 | buf[17]<<24);
        s32 alt  = (buf[22] | buf[23]<<8 | buf[24]<<16 | buf[25]<<24);

        u8 rx_chk_a = buf[34];
        u8 rx_chk_b = buf[35];

        u8 chk_a = 0, chk_b = 0;
        for(i=2; i<34; i++) {
            chk_a = chk_a + buf[i];
            chk_b = chk_b + chk_a;
        }

        if(chk_a != rx_chk_a || chk_b != rx_chk_b) {
            printf("Checksums didn't match: RX 0x%x%x, calc 0x%x%x\r\n",
                    rx_chk_a, rx_chk_b, chk_a, chk_b);
            continue;
        }

        printf("Got position: time %lu; lon %li; lat %li; alt %li\r\n",
                time, lon, lat, alt);

        altitude = alt / 1000;
        longitude = (double)lon / 10000000.0;
        latitude = (double)lat / 10000000.0;
        u8 dow = time / 86400000;
        u32 left = time - dow*86400000;
        hour = left / 3600000;
        left -= hour * 3600000;
        minute = left / 60000;
        left -= minute * 60000;
        second = left / 1000;

        char pre_sentence[256];
        sprintf(pre_sentence, "WOMBAT,%lu,%02u:%02u:%02u,%.5f,%.5f,%li",
                counter, hour, minute, second, latitude, longitude, altitude);

        u16 crc = 0xFFFF;
        /*u8 i;*/
        for(i=0; i<strlen(pre_sentence); i++) {
            crc = crc_update(crc, pre_sentence[i]);
        }
        char sentence[256];
        sprintf(sentence, "UUUUUUUUUU$$$%s*%X\n", pre_sentence, crc);
        printf("%s\r\n", sentence);
        /*radio_start();*/
        test_radio();
        led_turn_on(1);
        adf_transmit_string(sentence, ADF_50_BAUD);
        adf_transmit_string(sentence, ADF_50_BAUD);
        adf_transmit_string(sentence, ADF_50_BAUD);
        led_turn_off(1);
        adf_turn_off();
    }

    return 0;
}
