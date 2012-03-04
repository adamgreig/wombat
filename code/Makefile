# Modified from original for Wombat. Still in testing.

BINARY 			= wombat

##
## This file is part of the libopencm3 project.
##
## Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
## Copyright (C) 2010 Piotr Esden-Tempski <piotr@esden.net>
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
##

PREFIX			?= arm-none-eabi
CC				= $(PREFIX)-gcc
LD				= $(PREFIX)-gcc
OBJCOPY			= $(PREFIX)-objcopy
OBJDUMP			= $(PREFIX)-objdump
GDB				= $(PREFIX)-gdb
TOOLCHAIN_DIR   = libopencm3
CFLAGS			+= -Os -g -Wall -Wextra -I$(TOOLCHAIN_DIR)/include \
		   		   -fno-common -mcpu=cortex-m4 -mthumb -msoft-float -MD \
				   -DSTM32F4
LDSCRIPT		?= $(BINARY).ld
LDFLAGS			+= -lc -lnosys -L$(TOOLCHAIN_DIR)/lib \
				   -L$(TOOLCHAIN_DIR)/lib/stm32/f4 \
		   		   -T$(LDSCRIPT) -nostartfiles -Wl,--gc-sections \
		   		   -mthumb -mcpu=cortex-m4 -march=armv7 -mfix-cortex-m3-ldrd \
				   -msoft-float
OBJS			+= $(BINARY).o
OBJS 			= $(sort \
                  $(patsubst %.c,%.o,$(wildcard *.c)) \
                  $(patsubst %.s,%.o,$(wildcard *.s)))

OOCD			?= openocd
OOCD_INTERFACE 	?= interface/olimex-jtag-tiny
OOCD_BOARD 		?= openocd/wombat

# Black magic probe specific variables
# Set the BMP_PORT to a serial port and then BMP is used for flashing
BMP_PORT        ?=

# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q := @
NULL := 2>/dev/null
else
LDFLAGS += -Wl,--print-gc-sections
endif

.SUFFIXES: .elf .bin .hex .srec .list .images
.SECONDEXPANSION:
.SECONDARY:

all: images

images: $(BINARY).images
flash: $(BINARY).flash

%.images: %.bin %.hex %.srec %.list
	@#echo "*** $* images generated ***"

%.bin: %.elf
	@#printf "  OBJCOPY $(*).bin\n"
	$(Q)$(OBJCOPY) -Obinary $(*).elf $(*).bin

%.hex: %.elf
	@#printf "  OBJCOPY $(*).hex\n"
	$(Q)$(OBJCOPY) -Oihex $(*).elf $(*).hex

%.srec: %.elf
	@#printf "  OBJCOPY $(*).srec\n"
	$(Q)$(OBJCOPY) -Osrec $(*).elf $(*).srec

%.list: %.elf
	@#printf "  OBJDUMP $(*).list\n"
	$(Q)$(OBJDUMP) -S $(*).elf > $(*).list

%.elf: $(OBJS) $(LDSCRIPT) $(TOOLCHAIN_DIR)/lib/stm32/f4/libopencm3_stm32f4.a
	@#printf "  LD      $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(LD) -o $(*).elf $(OBJS) -lopencm3_stm32f4 $(LDFLAGS)

%.o: %.c Makefile
	@#printf "  CC      $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(Q)rm -f *.o
	$(Q)rm -f *.d
	$(Q)rm -f *.elf
	$(Q)rm -f *.bin
	$(Q)rm -f *.hex
	$(Q)rm -f *.srec
	$(Q)rm -f *.list

%.flash: %.hex
	@printf "  FLASH   $<\n"
	@# IMPORTANT: Don't use "resume", only "reset" will work correctly!
	$(Q)$(OOCD) -f $(OOCD_INTERFACE).cfg \
		    -f $(OOCD_BOARD).cfg \
		    -c "init" -c "reset init" \
		    -c "flash write_image erase $(*).hex" \
		    -c "reset" \
		    -c "shutdown" $(NULL)

.PHONY: images clean

-include $(OBJS:.o=.d)

