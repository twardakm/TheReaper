#include "NVIC.h"

void initializeNVIC()
{
	NVIC_InitTypeDef nvic_usart;
	nvic_usart.NVIC_IRQChannel = USART1_IRQn | USART2_IRQn;
	nvic_usart.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_usart.NVIC_IRQChannelSubPriority = 0;
	nvic_usart.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usart);
}
