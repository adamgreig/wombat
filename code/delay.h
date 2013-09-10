#ifndef WOMBAT_DELAY_H
#define WOMBAT_DELAY_H

#include <libopencm3/cm3/common.h>

void delay(uint32_t count);
void delay_ms(uint32_t ms);
void delay_ns(uint32_t ns);

#define DELAY_1_NS (uint32_t)(25)
#define DELAY_1_MS (uint32_t)(24740)

#define DELAY_MAX_NS (0xFFFFFFFF / DELAY_1_NS)
#define DELAY_MAX_MS (0xFFFFFFFF / DELAY_1_MS)

#endif
