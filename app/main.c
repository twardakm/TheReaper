#include <stdio.h>
#include <stdint.h>
#include "system_stm32f10x.h"
#include "stm32f10x_gpio.h"

#include "LED.h"
#include "APBClocks.h"

int main(void)
{
	SystemInit(); // powinno byc na 72 MHz ale sprawdzic!
	initializeAPB();

	GPIO_InitTypeDef ledy;
	ledy.GPIO_Mode = GPIO_Mode_Out_PP;
	ledy.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	ledy.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOC, &ledy);

	ledy.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12;

	GPIO_Init(GPIOA, &ledy);

	ledy.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;

	GPIO_Init(GPIOB, &ledy);

	GPIO_WriteBit(GPIOC, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12, Bit_SET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_6 | GPIO_Pin_7, Bit_SET);


    while(1)
    {
    }
}
