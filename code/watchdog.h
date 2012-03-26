#ifndef WOMBAT_WATCHDOG_H
#define WOMBAT_WATCHDOG_H

#include <libopencm3/stm32/iwdg.h>

void watchdog_setup();
void watchdog_reset();

#endif
