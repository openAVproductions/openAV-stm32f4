// Based on 02_gpio, modified to show how to use hardware FPU
// Harry van Haaren <harryhaaren@gmail.com>

// for math functions - *only* use sinf() absf()
// using the normal sin() will try to use a double variant!
#include <math.h>

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#define STACK_TOP 0x20000800

// Sys-Tick Counter - counts the number of instructions
// from German topic here: http://www.mikrocontroller.net/topic/261021#2708935
#define CORE_SysTickEn()    (*((u32*)0xE0001000)) = 0x40000001
#define CORE_SysTickDis()   (*((u32*)0xE0001000)) = 0x40000000
#define CORE_GetSysTick()   (*((u32*)0xE0001004))

static void nmi_handler(void);
static void hardfault_handler(void);
int main(void);

// Define the vector table
unsigned int *myvectors[4]
__attribute__ ((section("vectors"))) = {
  (unsigned int *) STACK_TOP,         // stack pointer
  (unsigned int *) main,              // code entry point
  (unsigned int *) nmi_handler,       // NMI handler (not really)
  (unsigned int *) hardfault_handler  // hard fault handler
};


void cortexm4f_enable_fpu(void)
{
  // set configurable flag on FPU - maybe not necessary?
  SCB->CPACR |= 0x00f00000; //fpu can be configured
  
  /* set CP10 and CP11 Full Access */
  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
}

int main(void)
{
  cortexm4f_enable_fpu();
  
  float x = 3.f;
  float y = 3.f;
  float z = 9.f;
  
  float out = 0.f;
  
  int i = 0;
  int j = 0;
  
  
  float f2 = 2.29f;
  CORE_SysTickEn();
  
  /// Crude approximation of the number of instructions required to perform each
  /// of a multiply, divide, sinf and sqrt. Use GDB to print the values. Example
  /// output of arm gcc without optimization on an F4:
  /*
    (gdb) p cyclesMultiply
    $10 = 10
    (gdb) p cyclesDivide
    $11 = 27
    (gdb) p cyclesSinf
    $12 = 71
    (gdb) p cyclesSqrtf
    $13 = 348
  */
  
  // multiply
  vu32 it = CORE_GetSysTick();
  f2 = 1.01f * f2;
  vu32 it2 = CORE_GetSysTick();
  vu32 cyclesMultiply = it2 - it;
  
  // divide
  it = CORE_GetSysTick();
  f2 = 1.01f / f2;
  it2 = CORE_GetSysTick();
  vu32 cyclesDivide = it2 - it;
  
  // sine
  it = CORE_GetSysTick();
  f2 = sinf( f2 );
  it2 = CORE_GetSysTick();
  vu32 cyclesSinf = it2 - it;
  
  // square root
  it = CORE_GetSysTick();
  f2 = sqrtf( f2 );
  it2 = CORE_GetSysTick();
  vu32 cyclesSqrtf = it2 - it;
  
  for(;;)
  {
    out = ( (x*y)/z ) * i;
    i++;
  }
}

void assert_param(u8* file, u32 line)
{
  // empty stub implementation of assert_param, to resolve undefined reference
}

void nmi_handler(void)
{
  for(;;);
}

void hardfault_handler(void)
{
  for(;;);
}
