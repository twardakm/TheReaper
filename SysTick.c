#include "SysTick.h"

void initializeSysTick()
{
	/*
	 * Interrupt every 1s:
	 * 72 MHz / 8 = 9 -> count to 9000000
	 */
	SysTick_Config(9000000ul);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

void SysTick_Handler(void)
{
   LED5_GPIO->ODR ^= LED5_PIN;
}
