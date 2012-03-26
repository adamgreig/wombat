#include <stdio.h>

#include "gps.h"

const u8 gps_status_request[8] = {
    0xB5, 0x62, 0x01, 0x03, 0x00, 0x00, 0x04, 0x0D};
const u8 gps_position_request[8] = {
    0xB5, 0x62, 0x01, 0x02, 0x00, 0x00, 0x03, 0x0A};
const u8 gps_time_request[8] = {
    0xB5, 0x62, 0x01, 0x21, 0x00, 0x00, 0x22, 0x67};

/* Create a filled in gps_data for later use. Sets impossible or invalid values
 * for everything to make it easy to spot if things are being used
 * unititialised (2989 = 0xBAD).
 */
gps_data gps_init_data(void) {
    gps_data data;
    data.latitude = 2989.0;
    data.longitude = 2989.0;
    data.altitude = -2989;
    data.hour = 99;
    data.minute = 99;
    data.second = 99;
    data.lock_valid = 255;
    data.data_valid = 0;
    return data;
}

void gps_peripheral_setup(void) {
    gpio_mode_setup(GPS_USART_GPIO, GPIO_MODE_AF, GPIO_PUPD_NONE,
            GPS_USART_PINS);
    // Set this manually for now, due to a libopencm3 bug
    /*gpio_set_af(GPS_USART_GPIO, GPS_USART_AF, GPS_USART_PINS);*/
    GPIOA_AFRL = (7 << 2*4) | (7 << 3*4);

	usart_set_baudrate(GPS_USART, 38400);
	usart_set_databits(GPS_USART, 8);
	usart_set_stopbits(GPS_USART, USART_STOPBITS_1);
	usart_set_mode(GPS_USART, USART_MODE_TX_RX);
	usart_set_parity(GPS_USART, USART_PARITY_NONE);
	usart_set_flow_control(GPS_USART, USART_FLOWCONTROL_NONE);

    usart_enable(GPS_USART);
}

void gps_request(const u8* message) {
    u8 i;
    for(i=0; i<8; i++)
        usart_send_blocking(GPS_USART, message[i]);
}

u8 gps_read_byte(void) {
    u16 b = usart_recv_blocking(GPS_USART);
    return (u8)(b & 0xFF);
}

void gps_read_message(u8* buffer, u8 length) {
    u8 i, b;
    for(i=0; i<length; i++) {
        b = gps_read_byte();
        if(i == 0 && b != 0xB5) {
            i--;
        } else {
            buffer[i] = b;
        }
    }
}

u16 gps_ubx_checksum(u8* bytes, u8 length) {
    u8 a = 0, b = 0;
    u16 i;
    for(i=0; i<length; i++) {
        a += bytes[i];
        b += a;
    }
    return (u16)a << 8 | (u16)b;
}

u8 gps_bad_header(u8* msg) {
    if(msg[0] != 0xB5 || msg[1] != 0x62)
        return 1;
    return 0;
}

u8 gps_bad_id(u8* msg, u8 id) {
    if(msg[2] != 0x01 || msg[3] != id)
        return 1;
    return 0;
}

u8 gps_bad_checksum(u8* msg, u8 length) {
    u8 rx_chk_a = msg[length - 2];
    u8 rx_chk_b = msg[length - 1];
    u16 calc_chk = gps_ubx_checksum(&msg[2], length - 4);
    u8 calc_chk_a = calc_chk >> 8;
    u8 calc_chk_b = calc_chk & 0xFF;
    if(calc_chk_a != rx_chk_a || calc_chk_b != rx_chk_b)
        return 1;
    return 0;
}

gps_data gps_get_status(void) {
    gps_data data = gps_init_data();
    u8 msg[24];
    gps_request(gps_status_request);
    gps_read_message(msg, 24);
    if(gps_bad_header(msg))
        return data;
    if(gps_bad_id(msg, 0x03))
        return data;
    if(gps_bad_checksum(msg, 24))
        return data;

    u8 status = msg[6+5];
    data.lock_valid = status & 0x01;

    data.data_valid = 1;
    
    return data;
}

gps_data gps_get_time(void) {
    gps_data data = gps_init_data();
    u8 msg[28];
    gps_request(gps_time_request);
    gps_read_message(msg, 28);
    if(gps_bad_header(msg))
        return data;
    if(gps_bad_id(msg, 0x21))
        return data;
    if(gps_bad_checksum(msg, 28))
        return data;

    u8 valid = msg[6+19];

    if(!valid & 0x01)
        // This checks for valid time of week, ignoring week number
        // and UTC (don't care if a few seconds out because we don't know
        // the current GPS-UTC offset, and don't care if we don't know the date
        // since we do not use it).
        return data;

    data.hour = msg[6+16];
    data.minute = msg[6+17];
    data.second = msg[6+18];

    data.data_valid = 1;
    return data;
}

gps_data gps_get_position(void) {
    gps_data data = gps_init_data();
    u8 msg[36];
    gps_request(gps_position_request);
    gps_read_message(msg, 36);
    if(gps_bad_header(msg))
        return data;
    if(gps_bad_id(msg, 0x02))
        return data;
    if(gps_bad_checksum(msg, 36))
        return data;

    s32 lon = (msg[10] | msg[11] << 8 | msg[12] << 16 | msg[13] << 24);
    s32 lat = (msg[14] | msg[15] << 8 | msg[16] << 16 | msg[17] << 24);
    s32 alt = (msg[22] | msg[23] << 8 | msg[24] << 16 | msg[25] << 24);

    data.latitude = (double)lat / (double)1E7;
    data.longitude = (double)lon / (double)1E7;
    data.altitude = alt / 1E3;

    if(data.latitude > 90.0 || data.latitude < -90.0)
        return data;
    if(data.longitude > 180.0 || data.longitude < -180.0)
        return data;

    data.data_valid = 1;
    return data;
}

gps_data gps_get_data(void) {
    gps_data data = gps_init_data();

    gps_data status = gps_get_status();
    if(status.data_valid) {
        data.lock_valid = status.lock_valid;
    } else {
        return data;
    }

    gps_data time = gps_get_time();
    if(time.data_valid) {
        data.hour = time.hour;
        data.minute = time.minute;
        data.second = time.second;
    } else {
        return data;
    }

    gps_data position = gps_get_position();
    if(position.data_valid) {
        data.latitude = position.latitude;
        data.longitude = position.longitude;
        data.altitude = position.altitude;
    } else {
        return data;
    }

    data.data_valid = 1;
    return data;
}
