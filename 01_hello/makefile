# Author of original Makefile: Wolfgang Wieser
# Code re-used with permission from this tutorial,
# http://www.triplespark.net/elec/pdev/arm/stm32.html

# With minor modifications by Harry van Haaren

# Cross compiler prefix
CCPREFIX = arm-none-eabi-
CC       = $(CCPREFIX)gcc
LD       = $(CCPREFIX)ld -v
CP       = $(CCPREFIX)objcopy
OD       = $(CCPREFIX)objdump

# -mfix-cortex-m3-ldrd should be enabled by default for Cortex M3. 
CFLAGS  =  -I. -c -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LFLAGS  = -Tstm32.ld -nostartfiles
CPFLAGS = -Obinary
ODFLAGS = -S

all: hello.bin

clean:
	-rm -f hello.lst *.o hello.elf hello.lst hello.bin

run: hello.bin
	$(STM32FLASH) hello.bin

hello.bin: hello.elf
	@echo "...copying"
	$(CP) $(CPFLAGS) hello.elf hello.bin
	$(OD) $(ODFLAGS) hello.elf > hello.lst

hello.elf: hello.o stm32.ld 
	@echo "..linking"
	$(LD) $(LFLAGS) -o hello.elf hello.o    

hello.o: hello.c
	@echo ".compiling"
	$(CC) $(CFLAGS) hello.c
