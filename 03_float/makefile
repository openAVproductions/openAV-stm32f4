# Based on 02_gpio tutorial

# Cross compiler prefix
CCPREFIX = arm-none-eabi-
CC       = $(CCPREFIX)gcc
LD       = $(CCPREFIX)gcc
CP       = $(CCPREFIX)objcopy
OD       = $(CCPREFIX)objdump

CFLAGS  =  -I. -c -fno-common -O0 -g -mcpu=cortex-m4 -DSTM32F40_41xxx

# Hardware Floating Point Unit flags 
#   1. Constants are interpreted as "single-precision" float, not double
CFLAGS += -fsingle-precision-constant
#   2. Set the float binary interface to "hardware"
CFLAGS += -mfloat-abi=hard -mthumb
#   3. Set the exact model of the hardware FPU
CFLAGS += -mfpu=fpv4-sp-d16

# Includes for the Cortex M4 CPU
CFLAGS += -I../STM32F401-Discovery_FW_V1.0.0/Libraries/CMSIS/Include/
# Includes for the STM32 F4 board
CFLAGS += -I../STM32F401-Discovery_FW_V1.0.0/Libraries/CMSIS/Device/ST/STM32F4xx/Include/
# Includes for the STM32 peripherals 
CFLAGS += -I../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/

LFLAGS  = -Tstm32.ld -nostartfiles
CPFLAGS = -Obinary
ODFLAGS = -S

all: float.bin

clean:
	-rm -f float.lst *.o float.elf float.lst float.bin

run: float.bin
	st-flash write float.bin 0x8000000

float.bin: float.elf
	@echo "...copying"
	$(CP) $(CPFLAGS) float.elf float.bin
	$(OD) $(ODFLAGS) float.elf > float.lst

float.elf: float.o firmware stm32.ld
	@echo "..linking"
	
	# *Explicitly* set the linker search path for -lm
	# /<path to ARM>/arm-none-eabi/lib/thumb/cortex-m4/float-abi-hard/fpuv4-sp-d16
	# on this Arch Linux machine, the below works:
	# /usr/arm-none-eabi/lib/armv7e-m/fpu/
	$(LD) $(LFLAGS) -o float.elf float.o -L/usr/arm-none-eabi/lib/armv7e-m/fpu/ -lc -lm

float.o: float.c
	@echo ".compiling"
	$(CC) $(CFLAGS) float.c


firmware: stm32f4xx_gpio.o stm32f4xx_rcc.o
	@echo ".firmware"

stm32f4xx_gpio.o: ../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
	$(CC) $(CFLAGS) ../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c

stm32f4xx_rcc.o:  ../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
	$(CC) $(CFLAGS) ../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
