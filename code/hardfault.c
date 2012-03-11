
#include <libopencm3/stm32/f4/rcc.h>
#include <libopencm3/stm32/f4/gpio.h>

void hard_fault_handler(void) {
    int i;
    RCC_AHB1ENR     |= (1<<2);
    GPIOC_MODER      = (1<<0) | (1<<2) | (1<<4) | (1<<6);
    while(1) {
        GPIOC_ODR        = (1<<3) | (1<<2) | (1<<1) | (1<<0);
        for(i=0; i<1000000; i++)
            __asm__("nop");
        GPIOC_ODR        = 0;
        for(i=0; i<1000000; i++)
            __asm__("nop");
    }
}
