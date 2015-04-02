#include "USART.h"

void initializeUSART()
{
	/*
	 * PIN configuration
	 */
	GPIO_InitTypeDef usart_gpio;

	usart_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	usart_gpio.GPIO_Pin = RX_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(RX_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = TX_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(TX_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = RX2_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(RX2_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = TX2_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(TX2_GPIO, &usart_gpio);

	/*
	 * USART configuration
	 */
	USART_Cmd(USART1, ENABLE);

	USART_InitTypeDef usart_conf;

	usart_conf.USART_BaudRate=9600;
	usart_conf.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart_conf.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	usart_conf.USART_Parity=USART_Parity_No;
	usart_conf.USART_StopBits=USART_StopBits_1;
	usart_conf.USART_WordLength=USART_WordLength_8b;

	USART_Init(USART1, &usart_conf);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_EnableIRQ(USART1_IRQn);

	/*
	 * USART2
	 */

	USART_Cmd(USART2, ENABLE);

	USART_Init(USART2, &usart_conf);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_EnableIRQ(USART2_IRQn);
}

void USARTInterrupt(USART_TypeDef *USARTx)
{
	/* RXNE handler */
	if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
	{
		LED4_GPIO->ODR ^= LED4_PIN;

		//Disable interrupt until all data is received
		USARTx->CR1 &= ~USART_CR1_RXNEIE;

		/*
		 * Proceed commands
		 */

		uint8_t data = USARTx->DR;
		if (data == 0xFF) // start command
		{
			while((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until next data
			data = USARTx->DR;

			switch(data)
			{
			case 0x00: //who am I?
				while ((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until line feed
				data = USARTx->DR;
				if (data == 0x0A) //line feed, everything ok.
				{
					LED1_GPIO->ODR ^= LED1_PIN;

					/*
					 * Send my name
					 *
					 * The Reaper
					 *
					 */

					uint8_t name[10] = {'T', 'h', 'e', ' ', 'R', 'e', 'a', 'p', 'e', 'r'};
					int i = 0;
					for (i = 0; i < 10; i++)
					{
						while ((USARTx->SR & USART_FLAG_TXE) == RESET) {}
						USARTx->DR = name[i];
					}

					// Send line feed
					while ((USARTx->SR & USART_FLAG_TXE) == RESET) {}
					USARTx->DR = 0x0A;
				}
				break;
			default:
				break;
			}
		}
		else
		{
			// error occured start interrupt
			USARTx->CR1 |= USART_CR1_RXNEIE;
			return;
		}

		//Enable interrupt
		USARTx->CR1 |= USART_CR1_RXNEIE;
	}
}

void USART1_IRQHandler(void)
{
	USARTInterrupt(USART1);
}

void USART2_IRQHandler(void)
{
	USARTInterrupt(USART2);
}
