#include "motor.h"

void initializePWMTimer()
{
	GPIO_InitTypeDef pwmgpio;
	pwmgpio.GPIO_Mode = GPIO_Mode_AF_PP;
	pwmgpio.GPIO_Speed = GPIO_Speed_50MHz;
	pwmgpio.GPIO_Pin = MOTOR_PWM_PIN;
	GPIO_Init(MOTOR_PWM_GPIO, &pwmgpio);

	pwmgpio.GPIO_Pin = TURN_SERVO_PWM_PIN;
	GPIO_Init(TURN_SERVO_PWM_GPIO, &pwmgpio);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

	/*
	 * TIM 2 is for motor PWM
	 */

	TIM2->CR1 &= 0b1111110000000000; // Reset control register
	TIM2->CR1 |= TIM_CR1_URS | TIM_CR1_CEN; // default values, enable timer, overflow event

	TIM2->PSC = 100;
	TIM2->ARR = 127; // ok 6 kHz Motor PWM

	TIM2->CCMR1 |= TIM_OCMode_PWM2 | TIM_OCMode_PWM2 << 8;

	TIM2->CCER |= TIM_OCPolarity_Low | TIM_CCER_CC1E; //Enable, inverted polarity

	// TIM2->CCR1 to control motor PWM

	/*
	 * TIM 3 is for servo PWM (50 Hz)
	 */
	TIM3->CR1 &= 0b1111110000000000;
	TIM3->CR1 |= TIM_CR1_URS | TIM_CR1_CEN;

	TIM3->PSC = 281;
	TIM3->ARR = 5100;

	TIM3->CCMR1 |= TIM_OCMode_PWM2 | TIM_OCMode_PWM2 << 8;
	TIM3->CCER |= TIM_OCPolarity_Low << 4 | TIM_CCER_CC2E;

	// 1,5 ms
	// TIM3->CCR2 for servo PWM
	TIM3->CCR2 = 127 + 255;
}

void initializeDirectionOutput()
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE); // Disable NJTRST, PB4 is Alternate Function
	GPIO_InitTypeDef dir;
	dir.GPIO_Mode = GPIO_Mode_Out_PP;
	dir.GPIO_Speed = GPIO_Speed_2MHz;
	dir.GPIO_Pin = MOTOR_DIR_PIN;
	GPIO_Init(MOTOR_DIR_GPIO, &dir);

	MOTOR_DIR_GPIO->ODR &= ~(MOTOR_DIR_PIN);
}
