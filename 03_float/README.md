STM32 F4 - Float Math
=====================

Read the accompanying tutorial on the STM32 here:
```
http://openavproductions.com/stm32-f4-discovery
```

Intro
-----
This code builds on the `02_gpio` example, and performs some floating-point 
math routines. As the STM32 F4 has a dedicated hardware Floating-Point-Unit (or 
FPU), we can perform float math calculations very quickly. This tutorial shows
how we set up the FPU, and compile some code to use it.

Using the Hardware FPU
----------------------
In order to enable the hardware FPU, we set some CFLAGS:
```
# Hardware Floating Point Unit flags 
#   1. Constants are interpreted as "single-precision" float, not double
CFLAGS += -fsingle-precision-constant
#   2. Set the float binary interface to "hardware"
CFLAGS += -mfloat-abi=hard
#   3. Set the exact model of the F4 boards hardware FPU
CFLAGS += -mfpu=fpv4-sp-d16
```
We must also explicitly link to libm (math) and libc (c runtime). Note that in
order to find the hard-FPU version of `libm`, we must tell the linker the search
path! This linux install (Arch Linux at 03-'15) the path is
`/usr/arm-none-eabi/lib/armv7e-m/fpu/`  Note that this path may (probably will)
be different on your own machine: many tutorials seem to quote
`<path to ARM>/arm-none-eabi/lib/thumb/cortex-m4/float-abi-hard/fpuv4-sp-d16` as
the library search path, YMMV.
```
$(LD) $(LFLAGS) -o float.elf float.o -L/usr/arm-none-eabi/lib/armv7e-m/fpu/ -lc -lm
```

To use some math functions like `sin()` we `#include <math.h>`. Note that we *must*
use the `sinf()` variant, otherwise double precision floating math will be used,
and the FPU cannot accellerate that!

Finally attach st-util to the F4, and then use GDB to print the values of the
instruction counter values that float.c calculates: sqrtf() is expensive!
```
(gdb) p cyclesMultiply
$10 = 10
(gdb) p cyclesDivide
$11 = 27
(gdb) p cyclesSinf
$12 = 71
(gdb) p cyclesSqrtf
$13 = 348
```

Double checking Hard FPU is working
-----------------------------------
As an exercise in understanding the compiled code for a hardware FPU, we look at
the generated assembly listing. During the compilation stage, the `float.lst` is
generated, which contains the annotated source for the `float.c` program. Note
that other files that are also linked in to the binary are also present.

Search for `int main(void)` in the `float.lst` file, and slowly read through the
instructions. Notice the comment lines are included in the assembly, making it
easier to understand what C code generates which assembly instructions.

In the `// multiply` section of code, we are particularly interested in checking
if the hardware floating-point instructions are used, or if the software float
instructions are utilized. The following snippet of output from `float.lst`
clearly shows that the `vmul.f32` instruction is used to perform the multiply.
The `vmul.f32` is a hardware NEON instruction, so we now know for sure that the
hard FPU code is working.
```
  // multiply
  vu32 it = CORE_GetSysTick();
  6e:	4b32      	ldr	r3, [pc, #200]	; (138 <main+0xf8>)
  70:	681b      	ldr	r3, [r3, #0]
  72:	61bb      	str	r3, [r7, #24]
  f2 = 1.01f * f2;
  74:	edd7 7a07 	vldr	s15, [r7, #28]
  78:	ed9f 7a30 	vldr	s14, [pc, #192]	; 13c <main+0xfc>
  7c:	ee67 7a87 	vmul.f32	s15, s15, s14
  80:	edc7 7a07 	vstr	s15, [r7, #28]
```


Conclusion
----------
We have learnt to target the hardware FPU, enabling much faster float 
calculations. We used some specific compiler flags to achieve this, and now 
we're ready to move on to more complex math projects on the F4.
