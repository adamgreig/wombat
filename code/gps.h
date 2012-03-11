#ifndef WOMBAT_GPS_H
#define WOMBAT_GPS_H

void gps_peripheral_setup(void);
void gps_request_position(void);
u8 gps_read_byte(void);

#endif
