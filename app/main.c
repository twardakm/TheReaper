#include <stdio.h>
#include <stdint.h>
#include "system_stm32f10x.h"
#include "stm32f10x.h"

#include "LED.h"
#include "APBClocks.h"
#include "SysTick.h"

int main(void)
{
	initializeAPB();
	initializeLEDGPIO();
	initializeSysTick();

    while(1)
    {
    }
}
