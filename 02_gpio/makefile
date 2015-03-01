# Based on 01_hello tutorial
# 

# Cross compiler prefix
CCPREFIX = arm-none-eabi-
CC       = $(CCPREFIX)gcc
LD       = $(CCPREFIX)ld -v
CP       = $(CCPREFIX)objcopy
OD       = $(CCPREFIX)objdump

# The STM32F40_41xxx define tells the firmware our target hardware
CFLAGS  =  -I. -c -fno-common -O0 -g -mcpu=cortex-m4 -mthumb -DSTM32F40_41xxx

# Includes for the Cortex M4 CPU
CFLAGS += -I../STM32F401-Discovery_FW_V1.0.0/Libraries/CMSIS/Include/
# Includes for the STM32 F4 baord
CFLAGS += -I../STM32F401-Discovery_FW_V1.0.0/Libraries/CMSIS/Device/ST/STM32F4xx/Include/
# Includes for the STM32 peripherals 
CFLAGS += -I../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/

LFLAGS  = -Tstm32.ld -nostartfiles
CPFLAGS = -Obinary
ODFLAGS = -S

all: gpio.bin

clean:
	-rm -f gpio.lst *.o gpio.elf gpio.lst gpio.bin

run: gpio.bin
	st-flash write gpio.bin 0x8000000

gpio.bin: gpio.elf
	@echo "...copying"
	$(CP) $(CPFLAGS) gpio.elf gpio.bin
	$(OD) $(ODFLAGS) gpio.elf > gpio.lst

gpio.elf: gpio.o firmware stm32.ld
	@echo "..linking"
	$(LD) $(LFLAGS) -o gpio.elf gpio.o stm32f4xx_gpio.o stm32f4xx_rcc.o

gpio.o: gpio.c
	@echo ".compiling"
	$(CC) $(CFLAGS) gpio.c


firmware: stm32f4xx_gpio.o stm32f4xx_rcc.o
	@echo ".firmware"

stm32f4xx_gpio.o: ../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
	$(CC) $(CFLAGS) ../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c

stm32f4xx_rcc.o:  ../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
	$(CC) $(CFLAGS) ../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
