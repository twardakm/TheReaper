#include "NVIC.h"

void initializeNVIC()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	NVIC_InitTypeDef nvic_TIM2;
	nvic_TIM2.NVIC_IRQChannel = TIM2_IRQn;
	nvic_TIM2.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_TIM2.NVIC_IRQChannelSubPriority = 0;
	nvic_TIM2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_TIM2);

	NVIC_InitTypeDef nvic_usart;
	nvic_usart.NVIC_IRQChannel = USART1_IRQn | USART2_IRQn;
	nvic_usart.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_usart.NVIC_IRQChannelSubPriority = 0;
	nvic_usart.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usart);
}
