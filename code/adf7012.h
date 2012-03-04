/*
 * ADF7012 Methods
 */

void adf_peripheral_setup(void);
void adf_default_config(void);
void adf_reset(void);
void adf_write_reg(uint32_t data);
void adf_transmit_byte(uint8_t byte);
void adf_transmit_string(char* data, uint32_t length);

/*
 * Timing
 */
#define ADF_1_MS        (u32)(10309)
#define ADF_50_BAUD     (u32)(206160)
#define ADF_300_BAUD    (u32)(34364)

/*
 * ADF7012 Pins
 */
#define ADF_CLK         GPIO5
#define ADF_CLK_PORT    GPIOA
#define ADF_DATA        GPIO7
#define ADF_DATA_PORT   GPIOA

#define ADF_CLKOUT      GPIO10
#define ADF_CLKOUT_PORT GPIOB
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

/*
 * ADF7012 Register Definitions
 */

/* Address bits */
#define ADF_C1          0
#define ADF_C2          1

/* ============================================== */
/* Register 0                                     */
/* ============================================== */

/* 11-Bit Frequency Error Correction */
#define ADF_R0_F1       2
#define ADF_R0_F2       3
#define ADF_R0_F3       4
#define ADF_R0_F4       5
#define ADF_R0_F5       6
#define ADF_R0_F6       7
#define ADF_R0_F7       8
#define ADF_R0_F8       9
#define ADF_R0_F9       10
#define ADF_R0_F10      11
#define ADF_R0_F11      12

/* 4-Bit R Dividerr */
#define ADF_R0_R1       13
#define ADF_R0_R2       14
#define ADF_R0_R3       15
#define ADF_R0_R4       16

/* Crystal Doubler */
#define ADF_R0_X1       17

/* XOEB */
#define ADF_R0_D1       18

/* Clock Out Divider */
#define ADF_R0_CL1      19
#define ADF_R0_CL2      20
#define ADF_R0_CL3      21
#define ADF_R0_CL4      22

/* VCO Adjust */
#define ADF_R0_VA1      23
#define ADF_R0_VA2      24

/* Output Divider */
#define ADF_R0_OD1      25
#define ADF_R0_OD2      26

/* ============================================== */
/* Register 1                                     */
/* ============================================== */

/* 12-Bit Fractional-N */
#define ADF_R1_M1       2
#define ADF_R1_M2       3
#define ADF_R1_M3       4
#define ADF_R1_M4       5
#define ADF_R1_M5       6
#define ADF_R1_M6       7
#define ADF_R1_M7       8
#define ADF_R1_M8       9
#define ADF_R1_M9       10
#define ADF_R1_M10      11
#define ADF_R1_M11      12
#define ADF_R1_M12      13

/* 8-Bit Integer-N */
#define ADF_R1_N1       14
#define ADF_R1_N2       15
#define ADF_R1_N3       16
#define ADF_R1_N4       17
#define ADF_R1_N5       18
#define ADF_R1_N6       19
#define ADF_R1_N7       20
#define ADF_R1_N8       21

/* Prescaler */
#define ADF_R1_P1       22

/* ============================================== */
/* Register 2                                     */
/* ============================================== */

/* Mod Control */
#define ADF_R2_S1       2
#define ADF_R2_S2       3

/* GOOK */
#define ADF_R2_G1       4

/* Power Amplifier */
#define ADF_R2_P1       5
#define ADF_R2_P2       6
#define ADF_R2_P3       7
#define ADF_R2_P4       8
#define ADF_R2_P5       9
#define ADF_R2_P6       10

/* Modulation Deviation */
#define ADF_R2_D1       11
#define ADF_R2_D2       12
#define ADF_R2_D3       13
#define ADF_R2_D4       14
#define ADF_R2_D5       15
#define ADF_R2_D6       16
#define ADF_R2_D7       17
#define ADF_R2_D8       18
#define ADF_R2_D9       19

/* GFSK Modulation Control */
#define ADF_R2_MC1      20
#define ADF_R2_MC2      21
#define ADF_R2_MC3      22

/* Index Counter */
#define ADF_R2_IC1      23
#define ADF_R2_IC2      24

/* ============================================== */
/* Register 3                                     */
/* ============================================== */

/* PLL Enable */
#define ADF_R3_PD1      2

/* PA Enable */
#define ADF_R3_PD2      3

/* CLKOUT Enable */
#define ADF_R3_PD3      4

/* Data Invert */
#define ADF_R3_I3       5

/* Charge Pump */
#define ADF_R3_CP1      6
#define ADF_R3_CP2      7

/* Bleed Current */
#define ADF_R3_CP3      8
#define ADF_R3_CP4      9

/* VCO Disable */
#define ADF_R3_VD       10

/* MUXOUT */
#define ADF_R3_M1       11
#define ADF_R3_M2       12
#define ADF_R3_M3       13
#define ADF_R3_M4       14

/* LD Precision */
#define ADF_R3_LD1      15

/* VCO Bias */
#define ADF_R3_VB1      16
#define ADF_R3_VB2      17
#define ADF_R3_VB3      18
#define ADF_R3_VB4      19

/* PA Bias */
#define ADF_R3_PA1      20
#define ADF_R3_PA2      21
#define ADF_R3_PA3      22

/* PLL Test Modes */
#define ADF_R3_PT1      23
#define ADF_R3_PT2      24
#define ADF_R3_PT3      25
#define ADF_R3_PT4      26
#define ADF_R3_PT5      27

/* SD Test Modes */
#define ADF_R3_ST1      28
#define ADF_R3_ST2      29
#define ADF_R3_ST3      30
#define ADF_R3_ST4      31

