// Code re-used with permission from this tutorial:
// http://www.triplespark.net/elec/pdev/arm/stm32.html
// By Wolfgang Wieser, heavily based on: 
// http://fun-tech.se/stm32/OlimexBlinky/mini.php

// With minor modifications by Harry van Haaren

#define STACK_TOP 0x20000800 // just a tiny stack for demo

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
  int i=0;
  
  for(;;)
  {
    i++;
  }
}

void nmi_handler(void)
{
  for(;;);
}

void hardfault_handler(void)
{
  for(;;);
}
