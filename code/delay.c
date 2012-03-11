#include "delay.h"

void delay(u32 count) {
    u32 i;
    for(i=0; i<count; i++)
        __asm__("nop");
}

void delay_ns(u32 ns) {
    if(ns > DELAY_MAX_NS) {
        u8 i;
        for(i=0; i<(ns / DELAY_MAX_NS) - 1; i++)
            delay(0xFFFFFFFF);
        delay(ns % DELAY_MAX_NS);
    } else {
        delay(ns * DELAY_1_NS);
    }
}

void delay_ms(u32 ms) {
    if(ms > DELAY_MAX_MS) {
        u8 i;
        for(i=0; i<(ms / DELAY_MAX_MS) - 1; i++)
            delay(0xFFFFFFFF);
        delay(ms % DELAY_MAX_MS);
    } else {
        delay(ms * DELAY_1_MS);
    }
}

