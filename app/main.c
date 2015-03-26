#include <stdio.h>
#include <stdint.h>
#include "system_stm32f10x.h"
#include "stm32f10x.h"

#include "LED.h"
#include "APBClocks.h"

int main(void)
{
	// powinno byc na 72 MHz ale sprawdzic!

	initializeAPB();
	initializeLEDGPIO();

    while(1)
    {
    }
}
