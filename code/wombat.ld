/* The 1M flash, 192K RAM STM32F405RGT6 part on Wombat. */
MEMORY
{
	rom (rx) :  ORIGIN = 0x08000000, LENGTH = 1M
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Include the common ld script from libopencm3. */
INCLUDE libopencm3_stm32f4.ld

