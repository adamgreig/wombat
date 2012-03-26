#include <libopencm3/stm32/f4/gpio.h>

#include "delay.h"
#include "adf.h"
#include "led.h"

// Configuration storage structs =============================================
struct {
    struct {
        u16 frequency_error_correction;
        u8 r_divider;
        u8 crystal_doubler;
        u8 crystal_oscillator_disable;
        u8 clock_out_divider;
        u8 vco_adjust;
        u8 output_divider;
    } r0;

    struct {
        u16 fractional_n;
        u8 integer_n;
        u8 prescaler;
    } r1;

    struct {
        u8 mod_control;
        u8 gook;
        u8 power_amplifier_level;
        u16 modulation_deviation;
        u8 gfsk_modulation_control;
        u8 index_counter;
    } r2;

    struct {
        u8 pll_enable;
        u8 pa_enable;
        u8 clkout_enable;
        u8 data_invert;
        u8 charge_pump_current;
        u8 bleed_up;
        u8 bleed_down;
        u8 vco_disable;
        u8 muxout;
        u8 ld_precision;
        u8 vco_bias;
        u8 pa_bias;
        u8 pll_test_mode;
        u8 sd_test_mode;
    } r3;
} adf_config;

// Prototypes for internal functions =========================================
void adf_set_pin_output(u32 prt, u16 pin);
void adf_set_pin_input(u32 prt, u16 pin);
void adf_reset_register_zero(void);
void adf_reset_register_one(void);
void adf_reset_register_two(void);
void adf_reset_register_three(void);
void adf_reset(void);
void adf_write_register_zero(void);
void adf_write_register_one(void);
void adf_write_register_two(void);
void adf_write_register_three(void);
void adf_write_register(u32 reg);
void adf_transmit_byte(u8 byte, u32 baud);
void adf_transmit_bit(u8 bit);
u8 adf_read_muxout(void);

// STM32 peripheral functions ================================================
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

// Configuration functions ===================================================

// Config resetting functions --------------------------------------------
void adf_reset_config(void) {
    adf_reset_register_zero();
    adf_reset_register_one();
    adf_reset_register_two();
    adf_reset_register_three();

    adf_reset();

    while(!adf_reg_ready());

    adf_write_config();
}

void adf_reset_register_zero(void) {
    adf_config.r0.frequency_error_correction = 0;
    adf_config.r0.r_divider = 1;
    adf_config.r0.crystal_doubler = ADF_OFF;
    adf_config.r0.crystal_oscillator_disable = ADF_OFF;
    adf_config.r0.clock_out_divider = 0;
    adf_config.r0.vco_adjust = 0;
    adf_config.r0.output_divider = 0;
}

void adf_reset_register_one(void) {
    adf_config.r1.fractional_n = 0;
    adf_config.r1.integer_n = 0;
    adf_config.r1.prescaler = ADF_PRESCALER_4_5;
}

void adf_reset_register_two(void) {
    adf_config.r2.mod_control = ADF_MODULATION_FSK;
    adf_config.r2.gook = ADF_OFF;
    adf_config.r2.power_amplifier_level = 0;
    adf_config.r2.modulation_deviation = 3;
    adf_config.r2.gfsk_modulation_control = 0;
    adf_config.r2.index_counter = 0;
}

void adf_reset_register_three(void) {
    adf_config.r3.pll_enable = ADF_OFF;
    adf_config.r3.pa_enable = ADF_OFF;
    adf_config.r3.clkout_enable = ADF_OFF;
    adf_config.r3.data_invert = ADF_OFF;
    adf_config.r3.charge_pump_current = ADF_CP_CURRENT_2_1;
    adf_config.r3.bleed_up = ADF_OFF;
    adf_config.r3.bleed_down = ADF_OFF;
    adf_config.r3.vco_disable = ADF_OFF;
    adf_config.r3.muxout = ADF_MUXOUT_REG_READY;
    adf_config.r3.ld_precision = ADF_LD_PRECISION_5_CYCLES;
    adf_config.r3.vco_bias = 6;
    adf_config.r3.pa_bias = 4;
    adf_config.r3.pll_test_mode = 0;
    adf_config.r3.sd_test_mode = 0;
}

void adf_reset(void) {
    gpio_clear(ADF_CE_PORT, ADF_CE);
    gpio_set(ADF_LE_PORT, ADF_LE);
    gpio_set(ADF_TXDATA_PORT, ADF_TXDATA);
    gpio_set(ADF_CLK_PORT, ADF_CLK);
    gpio_set(ADF_DATA_PORT, ADF_DATA);
    delay_ms(1);
    gpio_set(ADF_CE_PORT, ADF_CE);
    delay_ms(100);
}

void adf_turn_off(void) {
    gpio_clear(ADF_CE_PORT, ADF_CE);
}

// Configuration writing functions ---------------------------------------
void adf_write_config(void) {
    adf_write_register_zero();
    adf_write_register_one();
    adf_write_register_two();
    adf_write_register_three();
}

void adf_write_register_zero(void) {
    u32 reg =
        (0) |
        ((adf_config.r0.frequency_error_correction  & 0x7FF) <<  2) |
        ((adf_config.r0.r_divider                   & 0xF  ) << 13) |
        ((adf_config.r0.crystal_doubler             & 0x1  ) << 17) |
        ((adf_config.r0.crystal_oscillator_disable  & 0x1  ) << 18) |
        ((adf_config.r0.clock_out_divider           & 0xF  ) << 19) |
        ((adf_config.r0.vco_adjust                  & 0x3  ) << 23) |
        ((adf_config.r0.output_divider              & 0x3  ) << 25);
    adf_write_register(reg);
}

void adf_write_register_one(void) {
    u32 reg =
        (1) |
        ((adf_config.r1.fractional_n                & 0xFFF) <<  2) |
        ((adf_config.r1.integer_n                   & 0xFF ) << 14) |
        ((adf_config.r1.prescaler                   & 0x1  ) << 22);
    adf_write_register(reg);
}

void adf_write_register_two(void) {
    u32 reg =
        (2) |
        ((adf_config.r2.mod_control                 & 0x3  ) <<  2) |
        ((adf_config.r2.gook                        & 0x1  ) <<  4) |
        ((adf_config.r2.power_amplifier_level       & 0x3F ) <<  5) |
        ((adf_config.r2.modulation_deviation        & 0x1FF) << 11) |
        ((adf_config.r2.gfsk_modulation_control     & 0x7  ) << 20) |
        ((adf_config.r2.index_counter               & 0x3  ) << 23);
    adf_write_register(reg);
}

void adf_write_register_three(void) {
    u32 reg =
        (3) |
        ((adf_config.r3.pll_enable                  & 0x1  ) <<  2) |
        ((adf_config.r3.pa_enable                   & 0x1  ) <<  3) |
        ((adf_config.r3.clkout_enable               & 0x1  ) <<  4) |
        ((adf_config.r3.data_invert                 & 0x1  ) <<  5) |
        ((adf_config.r3.charge_pump_current         & 0x3  ) <<  6) |
        ((adf_config.r3.bleed_up                    & 0x1  ) <<  8) |
        ((adf_config.r3.bleed_down                  & 0x1  ) <<  9) |
        ((adf_config.r3.vco_disable                 & 0x1  ) << 10) |
        ((adf_config.r3.muxout                      & 0xF  ) << 11) |
        ((adf_config.r3.ld_precision                & 0x1  ) << 15) |
        ((adf_config.r3.vco_bias                    & 0xF  ) << 16) |
        ((adf_config.r3.pa_bias                     & 0x7  ) << 20) |
        ((adf_config.r3.pll_test_mode               & 0x1F ) << 23) |
        ((adf_config.r3.sd_test_mode                & 0xF  ) << 28);
    adf_write_register(reg);
}

void adf_write_register(u32 data) {
    s8 i;

    gpio_clear(ADF_CLK_PORT, ADF_CLK);
    delay_ns(20);

    gpio_clear(ADF_LE_PORT, ADF_LE);
    delay_ns(100);

    for(i=31; i>=0; i--) {
        if((data & (1<<i))>>i)
            gpio_set(ADF_DATA_PORT, ADF_DATA);
        else
            gpio_clear(ADF_DATA_PORT, ADF_DATA);
        delay_ns(20);
        gpio_set(ADF_CLK_PORT, ADF_CLK);
        delay_ns(100);
        gpio_clear(ADF_CLK_PORT, ADF_CLK);
        delay_ns(100);
    }

    delay_ns(20);
    gpio_set(ADF_LE_PORT, ADF_LE);
}

// Configuration setting functions ---------------------------------------
void adf_set_frequency_error_correction(u16 error) {
    adf_config.r0.frequency_error_correction = error;
}

void adf_set_r_divider(u8 r) {
    adf_config.r0.r_divider = r;
}

void adf_set_vco_adjust(u8 adjust) {
    adf_config.r0.vco_adjust = adjust;
}

void adf_set_frequency(u32 khz) {
    u32 f_pfd = 2458;
    u8 n = khz / f_pfd;
    u16 m = ((((khz*1000)/f_pfd) - (n * 1000)) * 4096) / 1000;
    adf_set_n(n);
    adf_set_m(m);
}

void adf_set_n(u8 n) {
    adf_config.r1.integer_n = n;
}

void adf_set_m(u16 m) {
    adf_config.r1.fractional_n = m;
}

void adf_set_pa_level(u8 level) {
    adf_config.r2.power_amplifier_level = level;
}

void adf_set_pll_enable(u8 enable) {
    adf_config.r3.pll_enable = enable;
}

void adf_set_pa_enable(u8 enable) {
    adf_config.r3.pa_enable = enable;
}

void adf_set_clkout_enable(u8 enable) {
    adf_config.r3.clkout_enable = enable;
}

void adf_set_charge_pump_current(u8 current) {
    adf_config.r3.charge_pump_current = current;
}

void adf_set_vco_disable(u8 disable) {
    adf_config.r3.vco_disable = disable;
}

void adf_set_muxout(u8 muxout) {
    adf_config.r3.muxout = muxout;
}

void adf_set_vco_bias(u8 bias) {
    adf_config.r3.vco_bias = bias;
}

void adf_set_pa_bias(u8 bias) {
    adf_config.r3.pa_bias = bias;
}

u8 adf_get_n() {
    return adf_config.r1.integer_n;
}

u16 adf_get_m() {
    return adf_config.r1.fractional_n;
}

void adf_setup(void) {
    adf_reset_config();
    adf_set_r_divider(2);
    /*adf_set_frequency(434000);*/
    adf_set_n(176);
    adf_set_m(2437);
    adf_set_pa_level(50);
    adf_set_muxout(ADF_MUXOUT_DIGITAL_LOCK);
    adf_set_pll_enable(ADF_ON);
    adf_write_config();
}

void adf_power_on(void) {
    adf_set_pa_enable(ADF_ON);
    adf_write_config();
}

void adf_power_off(void) {
    adf_set_pa_enable(ADF_OFF);
    adf_write_config();
}

// Data transmission functions ===============================================
void adf_transmit_string(char* data, u32 baud) {
    u32 i;
    for(i=0; data[i]; i++)
        adf_transmit_byte(data[i], baud);
}

void adf_transmit_byte(u8 byte, u32 baud) {
    s8 i;
    
    led_quickflash(LED4);

    // Start bit
    adf_transmit_bit(0);
    delay(baud);

    // Data byte
    for(i=0; i<8; i++) {
        if(byte & 1<<i)
            adf_transmit_bit(1);
        else
            adf_transmit_bit(0);
        delay(baud);
    }

    // Stop bits
    adf_transmit_bit(1);
    delay(baud);
    delay(baud);
}

void adf_transmit_bit(u8 bit) {
    if(bit) {
        gpio_set(ADF_TXDATA_PORT, ADF_TXDATA);
    } else {
        gpio_clear(ADF_TXDATA_PORT, ADF_TXDATA);
    }
}

// MUXOUT reading functions ==================================================
u8 adf_read_muxout(void) {
    return (u8)(gpio_get(ADF_MUXOUT_PORT, ADF_MUXOUT) > 0);
}

u8 adf_locked(void) {
    return adf_read_muxout();
}

u8 adf_reg_ready(void) {
    return adf_read_muxout();
}
