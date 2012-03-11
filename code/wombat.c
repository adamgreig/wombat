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
    /*led_peripheral_setup();*/
    /*adf_peripheral_setup();*/
    usart_peripheral_setup();
    gps_peripheral_setup();

    for(;;) {
        char buf[48];
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

        char sentence[256];
        s32 alt_m = alt / 1000;
        s32 lon_deg = lon / 10000000;
        s32 lon_decideg = lon % 10000000;
        if(lon_decideg < 0)
            lon_decideg = -lon_decideg;
        s32 lat_deg = lat / 10000000;
        s32 lat_decideg = lat % 10000000;
        if(lat_decideg < 0)
            lat_decideg = -lat_decideg;
        u8 dow = time / 86400000;
        u32 left = time - dow*86400000;
        u8 hr = left / 3600000;
        left -= hr * 3600000;
        u8 min = left / 60000;
        left -= min * 60000;
        u8 sec = left / 1000;

        sprintf(sentence,
                "$$WOMBAT,n,%02u:%02u:%02u,%li.%li,%li.%li,%li*ABCD\n",
                hr, min, sec, lat_deg, lat_decideg, lon_deg, lon_decideg,
                alt_m);

        printf("%s\r\n", sentence);
    }

    for(;;);
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

