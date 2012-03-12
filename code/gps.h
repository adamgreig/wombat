#ifndef WOMBAT_GPS_H
#define WOMBAT_GPS_H

void gps_peripheral_setup(void);
void gps_request_position(void);
u8 gps_read_byte(void);
void gps_get_position(double* latitude, double* longitude, s32* altitude,
        u8* hour, u8* minute, u8* second);

#endif
