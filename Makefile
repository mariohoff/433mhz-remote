#
# Makefile template for ATtiny85
# Derived from AVR Crosspack template
#

DEVICE     = attiny13           # See avr-help for all possible devices
CLOCK      = 9600000            # 9.6Mhz int Osc
PROGRAMMER = -c usbasp
#PROGRAMMER = -c arduino -b 19200 -P /dev/ttyUSB0  # For using Adafruit USBtiny
OBJECTS    = main.o rc.o        # Add more objects for each .c file here

# fuse settings:
# use http://www.engbedded.com/fusecalc
FUSES      = -U lfuse:w:0x7a:m -U hfuse:w:0xff:m # 9.6mhz

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -std=gnu99 -mmcu=$(DEVICE)

# symbolic targets:
all: main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash: all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm: main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c



