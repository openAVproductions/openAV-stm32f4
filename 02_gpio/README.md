STM32 F4 - Hello World
======================

Read the accompanying tutorial on the STM32 here:
```
http://openavproductions.com/stm32-f4-discovery
```

Intro
-----
This example blinks the LEDs that are mounted on the F4 Discovery board.
In order to blink the LEDs, we learn about setting up GPIO pins, and using
the firmware provided by ST for the F4 Discovery.

Notice
------
In order to compile this tutorial code, you *must* download the F4 firmware.
If you have not already done so, see the instructions in the top level README.

Using the GPIO pins
-------------------
In order to use the GPIO functionality of the F4, we must include the header
files provided by ST that describe the hardware. For this tutorial series, the
`makefile` is adapted to automatically include the relevant directories of the
firmware.

Includes and defines in the `makefile` to allow the compile to know where to
search for headers. Pay special attention to the `-DSTM32F40_41xxx`, as it
sets the hardware target, and the firmware will be compiled for exactly this board!
```
CFLAGS += -DSTM32F40_41xxx
# Includes for the Cortex M4 CPU
CFLAGS += -I../STM32F401-Discovery_FW_V1.0.0/Libraries/CMSIS/Include/
# Includes for the STM32 F4 baord
CFLAGS += -I../STM32F401-Discovery_FW_V1.0.0/Libraries/CMSIS/Device/ST/STM32F4xx/Include/
# Includes for the STM32 peripherals 
CFLAGS += -I../STM32F401-Discovery_FW_V1.0.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/
```

This section creates a firmware target, and we let it depend on all the source
files of the firmware that we require.
```
firmware: stm32f4xx_gpio.o stm32f4xx_rcc.o
	@echo ".firmware"
```


The next step is to include the header files we need: 
```
// F4 info, like LED4, BUTTON_USER etc
#include "stm32f4xx.h"
// Reset Clock Clear - RCC
#include "stm32f4xx_rcc.h"
// GPIO - General Purpose Input Output
#include "stm32f4xx_gpio.h"
```




Conclusion
----------
After finishing this tutorial you understand how the included firmware provides
access to the hardware peripherals on the F4 board. The modified `makefile`
compiles the necessary firmware files, and links them to the resulting binary.

