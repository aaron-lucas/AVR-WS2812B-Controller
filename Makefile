# ============================================================================
# LED Strip Controller - ATtiny85 MCU-based control of WS2812B LED Strips.
#
# Makefile
#
# Created On: 2020/12/02
#
# Copyright (C) 2020  Aaron Lucas
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# aaronlucas98@gmail.com
# https://github.com/aaron-lucas
# ============================================================================

# This is a prototype Makefile. Modify it according to your needs.
# You should at least check the settings for
# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected. We recommend that you leave it undefined and
#                add settings like this to your ~/.avrduderc file:
#                   default_programmer = "stk500v2"
#                   default_serial = "avrdoper"
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.

SRC	= src
OBJ = obj
BIN = bin
TMP = tmp

DEVICE     = attiny85
CLOCK      = 16000000
PROGRAMMER = usbasp
FUSES      = -U lfuse:w:0xf1:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m #-U lfuse:w:0xb1:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

SOURCES   	:= $(wildcard $(SRC)/*.c)
ASM_SOURCES := $(wildcard $(SRC)/*.S)
OBJECTS	  	:= $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES)) $(patsubst $(SRC)/%.S,$(OBJ)/%.o,$(ASM_SOURCES))
DEPENDS   	:= $(patsubst $(SRC)/%.c,$(OBJ)/%.d,$(SOURCES)) $(patsubst $(SRC)/%.S,$(OBJ)/%.d,$(ASM_SOURCES))
# OBJECTS    = $(OBJ)/ws2812b_control.o $(OBJ)/update_leds.o $(OBJ)/patterns.o $(OBJ)/rgb_data.o

AVRDUDE = avrdude -c $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -O2 -MMD -MP -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

.PRECIOUS: $(SRC)/update_leds.S
.PHONY: all clean

# symbolic targets:
all:	ws2812b_control

$(OBJ)/%.o: $(SRC)/%.c
	$(COMPILE) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.S
	$(COMPILE) -O0 -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

$(SRC)/%.s: $(SRC)/%.c
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:$(BIN)/ws2812b_control.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID $(BIN)/ws2812b_control.hex

clean:
	echo rm -f $(OBJECTS) $(DEPENDS) $(BIN)/*

# file targets:
$(BIN)/ws2812b_control.elf: $(OBJECTS)
	$(COMPILE) -o $(BIN)/ws2812b_control.elf $(OBJECTS)

ws2812b_control: $(BIN)/ws2812b_control.elf
	rm -f $(BIN)/ws2812b_control.hex
	avr-objcopy -j .text -j .data -O ihex $(BIN)/ws2812b_control.elf $(BIN)/ws2812b_control.hex
	avr-size --format=avr --mcu=$(DEVICE) $(BIN)/ws2812b_control.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	$(BIN)/ws2812b_control.elf
	avr-objdump -d $(BIN)/ws2812b_control.elf

cpp:
	$(COMPILE) -E $(SRC)/ws2812b_control.c
