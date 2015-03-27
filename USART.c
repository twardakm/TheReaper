#include "USART.h"

void initializeUSART()
{
	/*
	 * PIN configuration
	 */
	GPIO_InitTypeDef usart_gpio;

	usart_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	usart_gpio.GPIO_Pin = RX2_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(RX2_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = TX2_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(TX2_GPIO, &usart_gpio);

	/*
	 * USART configuration
	 */
	USART_Cmd(USART2, ENABLE);

	USART_InitTypeDef usart_conf;

	usart_conf.USART_BaudRate=9600;
	usart_conf.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart_conf.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	usart_conf.USART_Parity=USART_Parity_No;
	usart_conf.USART_StopBits=USART_StopBits_1;
	usart_conf.USART_WordLength=USART_WordLength_8b;

	USART_Init(USART2, &usart_conf);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_EnableIRQ(USART2_IRQn);

	LED1_GPIO->ODR ^= LED1_PIN;
}

void USART2_IRQHandler(void)
{
	/* RXNE handler */
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		LED1_GPIO->ODR ^= LED1_PIN;
		USART2->SR &= ~USART_FLAG_RXNE;
	}
}
