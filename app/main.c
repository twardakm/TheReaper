#include <stdio.h>
#include <stdint.h>
#include "system_stm32f10x.h"
#include "stm32f10x.h"

#include "LED.h"
#include "APBClocks.h"
#include "SysTick.h"
#include "USART.h"
#include "NVIC.h"
#include "motor.h"

int main(void)
{
	initializeAPB();
	initializeLEDGPIO();
	initializeSysTick();
	initializePWMTimer();

	initializeUSART();

	initializeNVIC();
    while(1)
    {
    }
}
