#include "delay.h"

void delay(uint32_t count) {
    uint32_t i;
    for(i=0; i<count; i++)
        __asm__("nop");
}

void delay_ns(uint32_t ns) {
    if(ns > DELAY_MAX_NS) {
        uint8_t i;
        for(i=0; i<(ns / DELAY_MAX_NS) - 1; i++)
            delay(0xFFFFFFFF);
        delay(ns % DELAY_MAX_NS);
    } else {
        delay(ns * DELAY_1_NS);
    }
}

void delay_ms(uint32_t ms) {
    if(ms > DELAY_MAX_MS) {
        uint8_t i;
        for(i=0; i<(ms / DELAY_MAX_MS) - 1; i++)
            delay(0xFFFFFFFF);
        delay(ms % DELAY_MAX_MS);
    } else {
        delay(ms * DELAY_1_MS);
    }
}

