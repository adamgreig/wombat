#ifndef WOMBAT_ADF_H
#define WOMBAT_ADF_H

#include <libopencm3/cm3/common.h>

// ADF API ===================================================================
void adf_peripheral_setup(void);
void adf_turn_off(void);
void adf_reset_config(void);
void adf_write_config(void);
void adf_transmit_string(char* data, uint32_t baud);
uint8_t adf_locked(void);
uint8_t adf_reg_ready(void);

void adf_set_frequency_error_correction(uint16_t error);
void adf_set_r_divider(uint8_t r);
void adf_set_vco_adjust(uint8_t adjust);
void adf_set_frequency(uint32_t khz);
void adf_set_n(uint8_t n);
void adf_set_m(uint16_t m);
void adf_set_pa_level(uint8_t level);
void adf_set_pll_enable(uint8_t enable);
void adf_set_pa_enable(uint8_t enable);
void adf_set_clkout_enable(uint8_t enable);
void adf_set_charge_pump_current(uint8_t current);
void adf_set_vco_disable(uint8_t disable);
void adf_set_muxout(uint8_t muxout);
void adf_set_vco_bias(uint8_t bias);
void adf_set_pa_bias(uint8_t bias);

void adf_setup(void);
void adf_power_on(void);
void adf_power_off(void);
uint8_t adf_lock(void);

uint8_t adf_get_n(void);
uint16_t adf_get_m(void);
uint8_t adf_get_vco_adjust(void);
uint8_t adf_get_vco_bias(void);

// The ADF7012 pin connections ===============================================
#define ADF_CLK         GPIO5
#define ADF_CLK_PORT    GPIOA
#define ADF_DATA        GPIO10
#define ADF_DATA_PORT   GPIOB
#define ADF_CLKOUT      GPIO7
#define ADF_CLKOUT_PORT GPIOA
#define ADF_CE          GPIO11
#define ADF_CE_PORT     GPIOB
#define ADF_LE          GPIO12
#define ADF_LE_PORT     GPIOB
#define ADF_TXCLK       GPIO13
#define ADF_TXCLK_PORT  GPIOB
#define ADF_MUXOUT      GPIO14
#define ADF_MUXOUT_PORT GPIOB
#define ADF_TXDATA      GPIO15
#define ADF_TXDATA_PORT GPIOB

// Timing constants ==========================================================
#define ADF_50_BAUD     (uint32_t)(479441)
#define ADF_300_BAUD    (uint32_t)(79915)
#define ADF_1200_BAUD   (uint32_t)(19979)

// General Purpose ===========================================================
#define ADF_OFF 0
#define ADF_ON  1

// Register Constants ========================================================
// Register 1 ----------------------------------------------------------------
#define ADF_PRESCALER_4_5 0
#define ADF_PRESCALER_8_9 1

// Register 2 ----------------------------------------------------------------
#define ADF_MODULATION_FSK 0
#define ADF_MODULATION_GFSK 1
#define ADF_MODULATION_ASK 2
#define ADF_MODULATION_OOK 3

// Register 3 ----------------------------------------------------------------
#define ADF_CP_CURRENT_0_3 0
#define ADF_CP_CURRENT_0_9 1
#define ADF_CP_CURRENT_1_5 2
#define ADF_CP_CURRENT_2_1 3
#define ADF_MUXOUT_LOGIC_LOW 0
#define ADF_MUXOUT_LOGIC_HIGH 1
#define ADF_MUXOUT_REG_READY 3
#define ADF_MUXOUT_DIGITAL_LOCK 4
#define ADF_MUXOUT_ANALOGUE_LOCK 5
#define ADF_MUXOUT_R_DIVIDER_2 6
#define ADF_MUXOUT_N_DIVIDER_2 7
#define ADF_MUXOUT_RF_R_DIVIDER 8
#define ADF_MUXOUT_DATA_RATE 9
#define ADF_MUXOUT_BATT_2_35 10
#define ADF_MUXOUT_BATT_2_75 11
#define ADF_MUXOUT_BATT_3 12
#define ADF_MUXOUT_BATT_3_25 13
#define ADF_MUXOUT_TEST_MODE 14
#define ADF_MUXOUT_SD_TEST_MODE 15
#define ADF_LD_PRECISION_3_CYCLES 0
#define ADF_LD_PRECISION_5_CYCLES 1

#endif
