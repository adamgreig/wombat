#include <stdio.h>
#include <libopencm3/stm32/f4/gpio.h>

#include "delay.h"
#include "adf.h"
#include "led.h"

// Configuration storage structs =============================================
struct {
    struct {
        uint16_t frequency_error_correction;
        uint8_t r_divider;
        uint8_t crystal_doubler;
        uint8_t crystal_oscillator_disable;
        uint8_t clock_out_divider;
        uint8_t vco_adjust;
        uint8_t output_divider;
    } r0;

    struct {
        uint16_t fractional_n;
        uint8_t integer_n;
        uint8_t prescaler;
    } r1;

    struct {
        uint8_t mod_control;
        uint8_t gook;
        uint8_t power_amplifier_level;
        uint16_t modulation_deviation;
        uint8_t gfsk_modulation_control;
        uint8_t index_counter;
    } r2;

    struct {
        uint8_t pll_enable;
        uint8_t pa_enable;
        uint8_t clkout_enable;
        uint8_t data_invert;
        uint8_t charge_pump_current;
        uint8_t bleed_up;
        uint8_t bleed_down;
        uint8_t vco_disable;
        uint8_t muxout;
        uint8_t ld_precision;
        uint8_t vco_bias;
        uint8_t pa_bias;
        uint8_t pll_test_mode;
        uint8_t sd_test_mode;
    } r3;
} adf_config;

// Prototypes for internal functions =========================================
void adf_set_pin_output(uint32_t prt, uint16_t pin);
void adf_set_pin_input(uint32_t prt, uint16_t pin);
void adf_reset_register_zero(void);
void adf_reset_register_one(void);
void adf_reset_register_two(void);
void adf_reset_register_three(void);
void adf_reset(void);
void adf_write_register_zero(void);
void adf_write_register_one(void);
void adf_write_register_two(void);
void adf_write_register_three(void);
void adf_write_register(uint32_t reg);
void adf_transmit_byte(uint8_t byte, uint32_t baud);
void adf_transmit_bit(uint8_t bit);
uint8_t adf_read_muxout(void);

// STM32 peripheral functions ================================================
void adf_set_pin_output(uint32_t prt, uint16_t pin) {
    gpio_mode_setup(prt, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin);
}

void adf_set_pin_input(uint32_t prt, uint16_t pin) {
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
    uint32_t reg =
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
    uint32_t reg =
        (1) |
        ((adf_config.r1.fractional_n                & 0xFFF) <<  2) |
        ((adf_config.r1.integer_n                   & 0xFF ) << 14) |
        ((adf_config.r1.prescaler                   & 0x1  ) << 22);
    adf_write_register(reg);
}

void adf_write_register_two(void) {
    uint32_t reg =
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
    uint32_t reg =
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

void adf_write_register(uint32_t data) {
    int8_t i;

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
void adf_set_frequency_error_correction(uint16_t error) {
    adf_config.r0.frequency_error_correction = error;
}

void adf_set_r_divider(uint8_t r) {
    adf_config.r0.r_divider = r;
}

void adf_set_vco_adjust(uint8_t adjust) {
    adf_config.r0.vco_adjust = adjust;
}

void adf_set_frequency(uint32_t khz) {
    uint32_t f_pfd = 24576;
    uint8_t n = (khz*10) / f_pfd;
    uint32_t m = (u64)((u64)khz * 10000) / f_pfd;
    m -= n * 1000;
    m *= 4096;
    m /= 1000;
    adf_set_n(n);
    adf_set_m((uint16_t)m);
}

void adf_set_n(uint8_t n) {
    adf_config.r1.integer_n = n;
}

void adf_set_m(uint16_t m) {
    adf_config.r1.fractional_n = m;
}

void adf_set_pa_level(uint8_t level) {
    adf_config.r2.power_amplifier_level = level;
}

void adf_set_pll_enable(uint8_t enable) {
    adf_config.r3.pll_enable = enable;
}

void adf_set_pa_enable(uint8_t enable) {
    adf_config.r3.pa_enable = enable;
}

void adf_set_clkout_enable(uint8_t enable) {
    adf_config.r3.clkout_enable = enable;
}

void adf_set_charge_pump_current(uint8_t current) {
    adf_config.r3.charge_pump_current = current;
}

void adf_set_vco_disable(uint8_t disable) {
    adf_config.r3.vco_disable = disable;
}

void adf_set_muxout(uint8_t muxout) {
    adf_config.r3.muxout = muxout;
}

void adf_set_vco_bias(uint8_t bias) {
    adf_config.r3.vco_bias = bias;
}

void adf_set_pa_bias(uint8_t bias) {
    adf_config.r3.pa_bias = bias;
}

uint8_t adf_get_n() {
    return adf_config.r1.integer_n;
}

uint16_t adf_get_m() {
    return adf_config.r1.fractional_n;
}

uint8_t adf_get_vco_adjust(void) {
    return adf_config.r0.vco_adjust;
}

uint8_t adf_get_vco_bias(void) {
    return adf_config.r3.vco_bias;
}

void adf_setup(void) {
    adf_reset_config();
    adf_set_r_divider(2);
    adf_set_frequency(434000);
    adf_set_muxout(ADF_MUXOUT_DIGITAL_LOCK);
    adf_set_pll_enable(ADF_ON);
    adf_write_config();
}

uint8_t adf_lock(void) {
    uint8_t adj = 0, bias = 5;
    while(!adf_locked()) {
        adf_set_vco_adjust(adj);
        adf_set_vco_bias(bias);
        adf_write_config();
        delay_ms(50);
        if(++bias == 14) {
            bias = 1;
            if(++adj == 4) {
                return 0;
            }
        }
    }
    return 1;
}

void adf_power_on(void) {
    adf_set_pa_enable(ADF_ON);
    adf_set_pa_level(60);
    adf_write_config();
}

void adf_power_off(void) {
    adf_set_pa_enable(ADF_OFF);
    adf_write_config();
}

// Data transmission functions ===============================================
void adf_transmit_string(char* data, uint32_t baud) {
    uint32_t i;
    for(i=0; data[i]; i++)
        adf_transmit_byte(data[i], baud);
}

void adf_transmit_byte(uint8_t byte, uint32_t baud) {
    int8_t i;
    
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

void adf_transmit_bit(uint8_t bit) {
    if(bit) {
        gpio_set(ADF_TXDATA_PORT, ADF_TXDATA);
    } else {
        gpio_clear(ADF_TXDATA_PORT, ADF_TXDATA);
    }
}

// MUXOUT reading functions ==================================================
uint8_t adf_read_muxout(void) {
    return (uint8_t)(gpio_get(ADF_MUXOUT_PORT, ADF_MUXOUT) > 0);
}

uint8_t adf_locked(void) {
    return adf_read_muxout();
}

uint8_t adf_reg_ready(void) {
    return adf_read_muxout();
}
