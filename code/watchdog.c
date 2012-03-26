#include <libopencm3/stm32/iwdg.h>

#include "watchdog.h"

void watchdog_setup(void) {
    IWDG_KR = 0x5555;
    IWDG_PR = 6;
    IWDG_KR = 0x5555;
    IWDG_RLR = 3000; // Approximate timeout is RLR * 8ms (so, 24 seconds)
    IWDG_KR = 0xCCCC;
}

void watchdog_reset(void) {
    IWDG_KR = 0xAAAA;
}
