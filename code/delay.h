#ifndef WOMBAT_DELAY_H
#define WOMBAT_DELAY_H

#include <libopencm3/cm3/common.h>

void delay(u32 count);
void delay_ms(u32 ms);
void delay_ns(u32 ns);

#define DELAY_1_NS (u32)(25)
#define DELAY_1_MS (u32)(24740)

#define DELAY_MAX_NS (0xFFFFFFFF / DELAY_1_NS)
#define DELAY_MAX_MS (0xFFFFFFFF / DELAY_1_MS)

#endif
