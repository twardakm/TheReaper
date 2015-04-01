#include <stdio.h>
#include <stdint.h>
#include "system_stm32f10x.h"
#include "stm32f10x.h"

#include "LED.h"
#include "APBClocks.h"
#include "SysTick.h"
#include "USART.h"

int main(void)
{
	initializeAPB();
	initializeLEDGPIO();
	initializeSysTick();


	initializeUSART();

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	NVIC_InitTypeDef nvic_usart;
	nvic_usart.NVIC_IRQChannel = USART1_IRQn;
	nvic_usart.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_usart.NVIC_IRQChannelSubPriority = 0;
	nvic_usart.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usart);

    while(1)
    {
    }
}
