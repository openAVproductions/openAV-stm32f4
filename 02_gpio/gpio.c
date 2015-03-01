// Based on 01_hello, modified to show how to write
// to the GPIO pins by Harry van Haaren <harryhaaren@gmail.com>

// includes here are not "local" includes - the -I flags in the makefile set the
// location to search for the includes. If this doesn't work, double check that
// the firmware has been extracted and is in the exact location as expected.
// Re-read the README file in the top level if you're not sure!


// F4 info, like LED4, BUTTON_USER etc
#include "stm32f4xx.h"

// Reset Clock Clear - RCC
#include "stm32f4xx_rcc.h"

// GPIO - General Purpose Input Output
#include "stm32f4xx_gpio.h"

#define STACK_TOP 0x20000800

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


int main(void)
{
  // tutorial here covers details on GPIO modes, PUSH PULL etc:
  // http://tecsploit.com/stm32f4-discovery/stm32f4-discovery-using-gpio-to-control-an-external-led/
  
  // Setup the Clock for GPIOD
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  // Set details on 
  GPIO_InitTypeDef GPIO_InitStruct;
  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  int index;
  while( 1 )
  {
    GPIO_SetBits  (GPIOD, GPIO_Pin_12 );
    GPIO_ResetBits(GPIOD, GPIO_Pin_15 );
    for (index = 0; index < 500000; index++);
    
    GPIO_SetBits  (GPIOD, GPIO_Pin_15 );
    GPIO_ResetBits(GPIOD, GPIO_Pin_12 );
    for (index = 0; index < 500000; index++);
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
