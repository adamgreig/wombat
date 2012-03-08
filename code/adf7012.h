/*
 * ADF7012 Methods
 */

void adf_peripheral_setup(void);
void adf_default_config(void);
void adf_reset(void);
void adf_wait_for_lock(void);
void adf_write_reg(uint32_t data);
void adf_transmit_byte(uint8_t byte);
void adf_transmit_string(char* data, uint32_t length);

/*
 * Timing
 */
#define ADF_1_MS        (u32)(24740)
#define ADF_50_BAUD     (u32)(4794412)
#define ADF_300_BAUD    (u32)(79915)

/*
 * ADF7012 Pins
 */
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

/*
 * ADF7012 Register Definitions
 */

/* Address bits */
#define ADF_C1          (1<<0)
#define ADF_C2          (1<<1)

/* ============================================== */
/* Register 0                                     */
/* ============================================== */

/* 11-Bit Frequency Error Correction */
#define ADF_R0_F1       (1<<2)
#define ADF_R0_F2       (1<<3)
#define ADF_R0_F3       (1<<4)
#define ADF_R0_F4       (1<<5)
#define ADF_R0_F5       (1<<6)
#define ADF_R0_F6       (1<<7)
#define ADF_R0_F7       (1<<8)
#define ADF_R0_F8       (1<<9)
#define ADF_R0_F9       (1<<10)
#define ADF_R0_F10      (1<<11)
#define ADF_R0_F11      (1<<12)

/* 4-Bit R Dividerr */
#define ADF_R0_R1       (1<<13)
#define ADF_R0_R2       (1<<14)
#define ADF_R0_R3       (1<<15)
#define ADF_R0_R4       (1<<16)

/* Crystal Doubler */
#define ADF_R0_X1       (1<<17)

/* XOEB */
#define ADF_R0_D1       (1<<18)

/* Clock Out Divider */
#define ADF_R0_CL1      (1<<19)
#define ADF_R0_CL2      (1<<20)
#define ADF_R0_CL3      (1<<21)
#define ADF_R0_CL4      (1<<22)

/* VCO Adjust */
#define ADF_R0_VA1      (1<<23)
#define ADF_R0_VA2      (1<<24)

/* Output Divider */
#define ADF_R0_OD1      (1<<25)
#define ADF_R0_OD2      (1<<26)

/* ============================================== */
/* Register 1                                     */
/* ============================================== */

/* 12-Bit Fractional-N */
#define ADF_R1_M1       (1<<2)
#define ADF_R1_M2       (1<<3)
#define ADF_R1_M3       (1<<4)
#define ADF_R1_M4       (1<<5)
#define ADF_R1_M5       (1<<6)
#define ADF_R1_M6       (1<<7)
#define ADF_R1_M7       (1<<8)
#define ADF_R1_M8       (1<<9)
#define ADF_R1_M9       (1<<10)
#define ADF_R1_M10      (1<<11)
#define ADF_R1_M11      (1<<12)
#define ADF_R1_M12      (1<<13)

/* 8-Bit Integer-N */
#define ADF_R1_N1       (1<<14)
#define ADF_R1_N2       (1<<15)
#define ADF_R1_N3       (1<<16)
#define ADF_R1_N4       (1<<17)
#define ADF_R1_N5       (1<<18)
#define ADF_R1_N6       (1<<19)
#define ADF_R1_N7       (1<<20)
#define ADF_R1_N8       (1<<21)

/* Prescaler */
#define ADF_R1_P1       (1<<22)

/* ============================================== */
/* Register 2                                     */
/* ============================================== */

/* Mod Control */
#define ADF_R2_S1       (1<<2)
#define ADF_R2_S2       (1<<3)

/* GOOK */
#define ADF_R2_G1       (1<<4)

/* Power Amplifier */
#define ADF_R2_P1       (1<<5)
#define ADF_R2_P2       (1<<6)
#define ADF_R2_P3       (1<<7)
#define ADF_R2_P4       (1<<8)
#define ADF_R2_P5       (1<<9)
#define ADF_R2_P6       (1<<10)

/* Modulation Deviation */
#define ADF_R2_D1       (1<<11)
#define ADF_R2_D2       (1<<12)
#define ADF_R2_D3       (1<<13)
#define ADF_R2_D4       (1<<14)
#define ADF_R2_D5       (1<<15)
#define ADF_R2_D6       (1<<16)
#define ADF_R2_D7       (1<<17)
#define ADF_R2_D8       (1<<18)
#define ADF_R2_D9       (1<<19)

/* GFSK Modulation Control */
#define ADF_R2_MC1      (1<<20)
#define ADF_R2_MC2      (1<<21)
#define ADF_R2_MC3      (1<<22)

/* Index Counter */
#define ADF_R2_IC1      (1<<23)
#define ADF_R2_IC2      (1<<24)

/* ============================================== */
/* Register 3                                     */
/* ============================================== */

/* PLL Enable */
#define ADF_R3_PD1      (1<<2)

/* PA Enable */
#define ADF_R3_PD2      (1<<3)

/* CLKOUT Enable */
#define ADF_R3_PD3      (1<<4)

/* Data Invert */
#define ADF_R3_I1       (1<<5)

/* Charge Pump */
#define ADF_R3_CP1      (1<<6)
#define ADF_R3_CP2      (1<<7)

/* Bleed Current */
#define ADF_R3_CP3      (1<<8)
#define ADF_R3_CP4      (1<<9)

/* VCO Disable */
#define ADF_R3_VD0      (1<<10)

/* MUXOUT */
#define ADF_R3_M1       (1<<11)
#define ADF_R3_M2       (1<<12)
#define ADF_R3_M3       (1<<13)
#define ADF_R3_M4       (1<<14)

/* LD Precision */
#define ADF_R3_LD1      (1<<15)

/* VCO Bias */
#define ADF_R3_VB1      (1<<16)
#define ADF_R3_VB2      (1<<17)
#define ADF_R3_VB3      (1<<18)
#define ADF_R3_VB4      (1<<19)

/* PA Bias */
#define ADF_R3_PA1      (1<<20)
#define ADF_R3_PA2      (1<<21)
#define ADF_R3_PA3      (1<<22)

/* PLL Test Modes */
#define ADF_R3_PT1      (1<<23)
#define ADF_R3_PT2      (1<<24)
#define ADF_R3_PT3      (1<<25)
#define ADF_R3_PT4      (1<<26)
#define ADF_R3_PT5      (1<<27)

/* SD Test Modes */
#define ADF_R3_ST1      (1<<28)
#define ADF_R3_ST2      (1<<29)
#define ADF_R3_ST3      (1<<30)
#define ADF_R3_ST4      (1<<31)

