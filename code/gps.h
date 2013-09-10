#ifndef WOMBAT_GPS_H
#define WOMBAT_GPS_H

#include <libopencm3/stm32/f4/gpio.h>
#include <libopencm3/stm32/usart.h>

typedef struct gps_data_struct {
    double latitude, longitude;
    int32_t altitude;
    uint8_t hour, minute, second, lock_valid, data_valid;
} gps_data;

void gps_peripheral_setup(void);
gps_data gps_get_data(void);

#define GPS_USART_GPIO GPIOA
#define GPS_USART_TX GPIO2  // This is the STM32's TX and the GPS's RX
#define GPS_USART_RX GPIO3  // (and vice versa)
#define GPS_USART_PINS (GPS_USART_TX | GPS_USART_RX)
#define GPS_USART_AF GPIO_AF7
#define GPS_USART USART2

#endif
