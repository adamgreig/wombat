#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/f4/gpio.h>

#include <stdio.h>

#include "gps.h"

void gps_peripheral_setup(void) {
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO3);

	usart_set_baudrate(USART2, 38400);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

    usart_enable(USART2);

    /*for(;;)*/
        /*usart_send_blocking(USART2, 'U');*/
}

void gps_request_position(void) {
    u8 req[8] = {0xB5, 0x62, 0x0A, 0x04, 0x00, 0x00, 0x0E, 0x34};
    u8 i;
    for(i=0; i<8; i++)
        usart_send_blocking(USART2, req[i]);
}

void gps_get_position(double* latitude, double* longitude, s32* altitude,
        u8* hour, u8* minute, u8* second) {
    char buf[36];
    u8 b, i;
    for(i=0; i<36; i++) {
        b = gps_read_byte();
        if(i == 0 && b != 0xB5) {
            i = 255;
            return;
        }
        buf[i] = b;
    }

    if(buf[0] != 0xB5 || buf[1] != 0x62) {
        printf("Received packet with bad sync bits 0x%x%x, skipping.\r\n",
                buf[0], buf[1]);
        return;
    }
    if(buf[2] != 0x01 || buf[3] != 0x02) {
        printf("Received packet with unexpected ID 0x%x%x, skipping.\r\n",
                buf[2], buf[3]);
        return;
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
        return;
    }

    printf("Got position: time %lu; lon %li; lat %li; alt %li\r\n",
            time, lon, lat, alt);

    *altitude = alt / 1000;
    *longitude = (double)lon / 10000000.0;
    *latitude = (double)lat / 10000000.0;
    u8 dow = time / 86400000;
    u32 left = time - dow*86400000;
    *hour = left / 3600000;
    left -= *hour * 3600000;
    *minute = left / 60000;
    left -= *minute * 60000;
    *second = left / 1000;
}

u8 gps_read_byte(void) {
    u16 b = usart_recv_blocking(USART2);
    return (u8)(b & 0xFF);
}
