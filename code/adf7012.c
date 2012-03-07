/*
 * ADF7012 stuff
 */

#include <libopencm3/stm32/f4/gpio.h>
#include "led.h"

#include "adf7012.h"

void adf_set_pin_output(u32 prt, u16 pin) {
    gpio_mode_setup(prt, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin);
}

void adf_set_pin_input(u32 prt, u16 pin) {
    gpio_mode_setup(prt, GPIO_MODE_INPUT, GPIO_PUPD_NONE, pin);
}

void adf_peripheral_setup() {
    adf_set_pin_output(ADF_CLK_PORT, ADF_CLK);
    adf_set_pin_output(ADF_DATA_PORT, ADF_DATA);

    adf_set_pin_output(ADF_CE_PORT, ADF_CE);
    adf_set_pin_output(ADF_LE_PORT, ADF_LE);
    adf_set_pin_output(ADF_TXCLK_PORT, ADF_TXCLK);
    adf_set_pin_output(ADF_TXDATA_PORT, ADF_TXDATA);
    adf_set_pin_input(ADF_MUXOUT_PORT, ADF_MUXOUT);
    adf_set_pin_input(ADF_CLKOUT_PORT, ADF_CLKOUT);

}

void adf_wait(u32 count) {
    u32 i;
    for(i=0; i<count; i++)
        __asm__("nop");
}

void adf_wait_ms(u16 ms) {
    adf_wait(ms * ADF_1_MS);
}


void adf_default_config() {
    /* Toggle CE, resetting everything */
    adf_reset();

    /* Wait for regulator ready */
    adf_wait_ms(100);
    while(!gpio_get(ADF_MUXOUT_PORT, ADF_MUXOUT)) {
        led_turn_on(3);
        adf_wait_ms(100);
        led_turn_off(3);
        adf_wait_ms(100);
    }

    /* Register 0 -- R set to 1, clock divide set to 2 */
    adf_write_reg(
        0*ADF_C1     | 0*ADF_C2     |
        1*ADF_R0_R1  | 0*ADF_R0_R2  | 0*ADF_R0_R3  | 0*ADF_R0_R4  |
        1*ADF_R0_CL1 | 0*ADF_R0_CL2 | 0*ADF_R0_CL3 | 0*ADF_R0_CL4
    );

    /* Register 1 -- N set to 88.28125 */
    u8  n = 88;
    u16 m = 600;
    adf_write_reg(
        1*ADF_C1  | 0*ADF_C2  |
        n << 14 |
        m << 2
    );

    /* Register 2 -- PA set to 50%, deviation index set to 1 */
    adf_write_reg(
        0*ADF_C1  | 1*ADF_C2   |
        ADF_R2_P6 |      /* PA set to 50% power      */
        ADF_R2_D1        /* Deviation index set to 1 */
    );

    /* Register 3 */
    adf_write_reg(
        1*ADF_C1     | 1*ADF_C2     |
        1*ADF_R3_PD1 |                      /* PLL enable           */
        0*ADF_R3_PD2 |                      /* PA disable           */
        1*ADF_R3_PD3 |                      /* CLKOUT enable        */
        1*ADF_R3_CP1 | 1*ADF_R3_CP2 |       /* CP current 2.1mA     */
        0*ADF_R3_CP3 | 0*ADF_R3_CP4 |       /* Bleed current off    */
        0*ADF_R3_VD0 |                      /* VCO enable           */
        ADF_R3_M3    |                      /* Digital PLL lock     */
      //ADF_R3_M3 | ADF_R3_M1 |             /* Analog PLL lock      */
      //ADF_R3_M2 | ADF_R3_M3 |             /* R divider/2          */
      //ADF_R3_M1 | ADF_R3_M2 | ADF_R3_M3   /* N divider/2          */
        1*ADF_R3_LD1 |                      /* LD precision 5 cycles*/
        0*ADF_R3_VB1 | 1*ADF_R3_VB2 |       /* VCO bias current:    */
        1*ADF_R3_VB3 | 0*ADF_R3_VB4 |       /*     3mA              */
        0*ADF_R3_PA1 | 0*ADF_R3_PA2 |       /* PA bias current:     */
        1*ADF_R3_PA3                        /*     9uA              */
    );

    /* Wait for digital lock */
    /*while(!gpio_get(ADF_MUXOUT_PORT, ADF_MUXOUT)) {*/
        /*led_turn_on(2);*/
        /*adf_wait_ms(100);*/
        /*led_turn_off(2);*/
        /*adf_wait_ms(100);*/
    /*}*/

    /* Actually cycle through useful debug modes for a bit */
    /*for(;;) {*/
        /*[> DIGITAL LOCK <]*/
        /*adf_write_reg(*/
            /*1*ADF_C1     | 1*ADF_C2     |*/
            /*1*ADF_R3_PD1 |                      [> PLL enable           <]*/
            /*0*ADF_R3_PD2 |                      [> PA disable           <]*/
            /*1*ADF_R3_PD3 |                      [> CLKOUT enable        <]*/
            /*1*ADF_R3_CP1 | 1*ADF_R3_CP2 |       [> CP current 2.1mA     <]*/
            /*0*ADF_R3_CP3 | 0*ADF_R3_CP4 |       [> Bleed current off    <]*/
            /*0*ADF_R3_VD0 |                      [> VCO enable           <]*/
            /*ADF_R3_M3    |                      [> Digital PLL lock     <]*/
          /*//ADF_R3_M3 | ADF_R3_M1 |             [> Analog PLL lock      <]*/
          /*//ADF_R3_M2 | ADF_R3_M3 |             [> R divider/2          <]*/
          /*//ADF_R3_M1 | ADF_R3_M2 | ADF_R3_M3   [> N divider/2          <]*/
            /*1*ADF_R3_LD1 |                      [> LD precision 5 cycles<]*/
            /*0*ADF_R3_VB1 | 1*ADF_R3_VB2 |       [> VCO bias current:    <]*/
            /*1*ADF_R3_VB3 | 0*ADF_R3_VB4 |       [>     3mA              <]*/
            /*0*ADF_R3_PA1 | 0*ADF_R3_PA2 |       [> PA bias current:     <]*/
            /*1*ADF_R3_PA3                        [>     9uA              <]*/
        /*);*/
        /*led_turn_on(0);*/
        /*adf_wait_ms(1500);*/
        /*led_turn_off(0);*/

        /*[> ANALOG LOCK <]*/
        /*adf_write_reg(*/
            /*1*ADF_C1     | 1*ADF_C2     |*/
            /*1*ADF_R3_PD1 |                      [> PLL enable           <]*/
            /*0*ADF_R3_PD2 |                      [> PA disable           <]*/
            /*1*ADF_R3_PD3 |                      [> CLKOUT enable        <]*/
            /*1*ADF_R3_CP1 | 1*ADF_R3_CP2 |       [> CP current 2.1mA     <]*/
            /*0*ADF_R3_CP3 | 0*ADF_R3_CP4 |       [> Bleed current off    <]*/
            /*0*ADF_R3_VD0 |                      [> VCO enable           <]*/
          /*//ADF_R3_M3    |                      [> Digital PLL lock     <]*/
            /*ADF_R3_M3 | ADF_R3_M1 |             [> Analog PLL lock      <]*/
          /*//ADF_R3_M2 | ADF_R3_M3 |             [> R divider/2          <]*/
          /*//ADF_R3_M1 | ADF_R3_M2 | ADF_R3_M3   [> N divider/2          <]*/
            /*1*ADF_R3_LD1 |                      [> LD precision 5 cycles<]*/
            /*0*ADF_R3_VB1 | 1*ADF_R3_VB2 |       [> VCO bias current:    <]*/
            /*1*ADF_R3_VB3 | 0*ADF_R3_VB4 |       [>     3mA              <]*/
            /*0*ADF_R3_PA1 | 0*ADF_R3_PA2 |       [> PA bias current:     <]*/
            /*1*ADF_R3_PA3                        [>     9uA              <]*/
        /*);*/
        /*led_turn_on(1);*/
        /*adf_wait_ms(1500);*/
        /*led_turn_off(1);*/

        /*[> R divider/2 <]*/
        /*adf_write_reg(*/
            /*1*ADF_C1     | 1*ADF_C2     |*/
            /*1*ADF_R3_PD1 |                      [> PLL enable           <]*/
            /*0*ADF_R3_PD2 |                      [> PA disable           <]*/
            /*1*ADF_R3_PD3 |                      [> CLKOUT enable        <]*/
            /*1*ADF_R3_CP1 | 1*ADF_R3_CP2 |       [> CP current 2.1mA     <]*/
            /*0*ADF_R3_CP3 | 0*ADF_R3_CP4 |       [> Bleed current off    <]*/
            /*0*ADF_R3_VD0 |                      [> VCO enable           <]*/
          /*//ADF_R3_M3    |                      [> Digital PLL lock     <]*/
          /*//ADF_R3_M3 | ADF_R3_M1 |             [> Analog PLL lock      <]*/
            /*ADF_R3_M2 | ADF_R3_M3 |             [> R divider/2          <]*/
          /*//ADF_R3_M1 | ADF_R3_M2 | ADF_R3_M3   [> N divider/2          <]*/
            /*1*ADF_R3_LD1 |                      [> LD precision 5 cycles<]*/
            /*0*ADF_R3_VB1 | 1*ADF_R3_VB2 |       [> VCO bias current:    <]*/
            /*1*ADF_R3_VB3 | 0*ADF_R3_VB4 |       [>     3mA              <]*/
            /*0*ADF_R3_PA1 | 0*ADF_R3_PA2 |       [> PA bias current:     <]*/
            /*1*ADF_R3_PA3                        [>     9uA              <]*/
        /*);*/
        /*led_turn_on(2);*/
        /*adf_wait_ms(1500);*/
        /*led_turn_off(2);*/

        /*[> N divider/2 <]*/
        /*adf_write_reg(*/
            /*1*ADF_C1     | 1*ADF_C2     |*/
            /*1*ADF_R3_PD1 |                      [> PLL enable           <]*/
            /*0*ADF_R3_PD2 |                      [> PA disable           <]*/
            /*1*ADF_R3_PD3 |                      [> CLKOUT enable        <]*/
            /*1*ADF_R3_CP1 | 1*ADF_R3_CP2 |       [> CP current 2.1mA     <]*/
            /*0*ADF_R3_CP3 | 0*ADF_R3_CP4 |       [> Bleed current off    <]*/
            /*0*ADF_R3_VD0 |                      [> VCO enable           <]*/
          /*//ADF_R3_M3    |                      [> Digital PLL lock     <]*/
          /*//ADF_R3_M3 | ADF_R3_M1 |             [> Analog PLL lock      <]*/
          /*//ADF_R3_M2 | ADF_R3_M3 |             [> R divider/2          <]*/
            /*ADF_R3_M1 | ADF_R3_M2 | ADF_R3_M3 | [> N divider/2          <]*/
            /*1*ADF_R3_LD1 |                      [> LD precision 5 cycles<]*/
            /*0*ADF_R3_VB1 | 1*ADF_R3_VB2 |       [> VCO bias current:    <]*/
            /*1*ADF_R3_VB3 | 0*ADF_R3_VB4 |       [>     3mA              <]*/
            /*0*ADF_R3_PA1 | 0*ADF_R3_PA2 |       [> PA bias current:     <]*/
            /*1*ADF_R3_PA3                        [>     9uA              <]*/
        /*);*/
        /*led_turn_on(3);*/
        /*adf_wait_ms(1500);*/
        /*led_turn_off(3);*/
    /*}*/

    /* Assume digital lock detect is broken, just wait a short while */
    adf_wait_ms(500);
    led_turn_on(3);

    /* Register 3, PA on */
    adf_write_reg(
        1*ADF_C1     | 1*ADF_C2     |
        1*ADF_R3_PD1 |                      /* PLL enable           */
        1*ADF_R3_PD2 |                      /* PA enable            */
        1*ADF_R3_PD3 |                      /* CLKOUT enable        */
        1*ADF_R3_CP1 | 1*ADF_R3_CP2 |       /* CP current 2.1mA     */
        0*ADF_R3_CP3 | 0*ADF_R3_CP4 |       /* Bleed current off    */
        0*ADF_R3_VD0 |                      /* VCO enable           */
        ADF_R3_M3    |                      /* Digital PLL lock     */
      //ADF_R3_M3 | ADF_R3_M1 |             /* Analog PLL lock      */
      //ADF_R3_M2 | ADF_R3_M3 |             /* R divider/2          */
      //ADF_R3_M1 | ADF_R3_M2 | ADF_R3_M3   /* N divider/2          */
        1*ADF_R3_LD1 |                      /* LD precision 5 cycles*/
        0*ADF_R3_VB1 | 1*ADF_R3_VB2 |       /* VCO bias current:    */
        1*ADF_R3_VB3 | 0*ADF_R3_VB4 |       /*     3mA              */
        0*ADF_R3_PA1 | 0*ADF_R3_PA2 |       /* PA bias current:     */
        1*ADF_R3_PA3                        /*     9uA              */
    );

}

void adf_reset() {
    gpio_clear(ADF_CE_PORT, ADF_CE);
    gpio_set(ADF_LE_PORT, ADF_LE);
    gpio_set(ADF_TXDATA_PORT, ADF_TXDATA);
    gpio_set(ADF_CLK_PORT, ADF_CLK);
    gpio_set(ADF_DATA_PORT, ADF_DATA);
    adf_wait_ms(100);
    gpio_set(ADF_CE_PORT, ADF_CE);
    adf_wait_ms(100);
}

void adf_write_reg(u32 data) {
    s8 i;

    gpio_clear(ADF_LE_PORT, ADF_LE);
    adf_wait_ms(2);
    for(i=31; i>=0; i--) {
        if((data & (1<<i))>>i)
            gpio_set(ADF_DATA_PORT, ADF_DATA);
        else
            gpio_clear(ADF_DATA_PORT, ADF_DATA);
        adf_wait_ms(2);
        gpio_set(ADF_CLK_PORT, ADF_CLK);
        adf_wait_ms(2);
        gpio_clear(ADF_CLK_PORT, ADF_CLK);
        adf_wait_ms(2);
    }
    gpio_set(ADF_LE_PORT, ADF_LE);
    adf_wait_ms(2);
}

void adf_transmit_bit(u8 bit) {
    if(bit)
        gpio_set(ADF_TXDATA_PORT, ADF_TXDATA);
    else
        gpio_clear(ADF_TXDATA_PORT, ADF_TXDATA);
}

void adf_transmit_byte(u8 byte) {
    s8 i;

    /* START */
    adf_transmit_bit(0);
    adf_wait(ADF_50_BAUD);

    /* DATA */
    for(i=0; i<8; i++) {
        if(byte & 1<<i)
            adf_transmit_bit(1);
        else
            adf_transmit_bit(0);
        adf_wait(ADF_50_BAUD);
    }

    /* STOP */
    adf_transmit_bit(1);
    adf_wait(ADF_50_BAUD);
    adf_wait(ADF_50_BAUD);

    if(gpio_get(ADF_MUXOUT_PORT, ADF_MUXOUT)) {
        led_turn_off(1);
        led_turn_on(0);
    } else {
        led_turn_off(0);
        led_turn_on(1);
    }
}

void adf_wait_for_lock(void) {
    while(!gpio_get(ADF_MUXOUT_PORT, ADF_MUXOUT)) {
        led_turn_off(0);
        adf_default_config();
        led_turn_on(3);
        adf_wait_ms(100);
        led_turn_off(3);
    }
    led_turn_on(0);
    adf_wait_ms(100);
}

void adf_transmit_string(char* data, u32 length) {
    u32 i;

    for(i=0; i<length; i++)
        adf_transmit_byte(data[i]);
}

