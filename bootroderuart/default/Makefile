###############################################################################
# Makefile for the project bootroderuart
###############################################################################

## General Flags
PROJECT = bootroderuart
MCU = atmega2560
TARGET = bootroderuart.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99     -DF_CPU=7372800UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=bootroderuart.map
LDFLAGS += -Wl,-section-start=.text=0x3f000


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = bootroder.o berify.o main.o read.o spl.o spm.o mcu1.o mcu2.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) bootroderuart.hex bootroderuart.eep bootroderuart.lss size

## Compile
bootroder.o: ../bootroder.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

berify.o: ../berify.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

read.o: ../read.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

spl.o: ../spl.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

spm.o: ../spm.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mcu1.o: ../mcu1.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mcu2.o: ../mcu2.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) bootroderuart.elf dep/* bootroderuart.hex bootroderuart.eep bootroderuart.lss bootroderuart.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

