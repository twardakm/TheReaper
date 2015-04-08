#include "motor.h"

/*
 * On PCB is fail: PWM to servo is on the same timer as PWM to motor
 * TIM2 is set to 1 kHz with interrupt. Every interrupt servoPWM++.
 */
volatile uint8_t servoPWM = 0;

void initializePWMTimer()
{
	GPIO_InitTypeDef pwmgpio;
	pwmgpio.GPIO_Mode = GPIO_Mode_AF_PP;
	pwmgpio.GPIO_Speed = GPIO_Speed_50MHz;
	pwmgpio.GPIO_Pin = MOTOR_PWM_PIN;
	GPIO_Init(MOTOR_PWM_GPIO, &pwmgpio);

	pwmgpio.GPIO_Pin = TURN_SERVO_PWM_PIN;
	GPIO_Init(TURN_SERVO_PWM_GPIO, &pwmgpio);

	TIM2->CR1 &= 0b1111110000000000; // Reset control register
	TIM2->CR1 |= TIM_CR1_URS | TIM_CR1_CEN; // default values, enable timer, overflow event

	TIM2->PSC = 281;
	TIM2->ARR = 255;

	TIM2->CCMR1 |= TIM_OCMode_PWM2 | TIM_OCMode_PWM2 << 8;

	TIM2->CCER |= TIM_OCPolarity_Low << 4 | TIM_OCPolarity_Low | TIM_CCER_CC1E; //Enable, inverted polarity

	// TIM2->CCR1 to control motor PWM
	// TIM2->CCR2 to control servo PWM

	TIM2->DIER |= TIM_DIER_UIE; // enable interrupt
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
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

void TIM2_IRQHandler(void)
{
	if (TIM2->SR & TIM_SR_UIF)
	{
		// clear interrupt FLAG
		TIM2->SR &= ~TIM_IT_Update;

		if(servoPWM % 20 == 0) // 1 ms high voltage
		{
			TURN_SERVO_PWM_GPIO->CRL &= ~(0b11 << 6); // change TURN_SERVO_PWM_PIN to general output
			TURN_SERVO_PWM_GPIO->ODR |= TURN_SERVO_PWM_PIN;

			servoPWM = 0;
		}
		else if(servoPWM % 20 == 1) // enable PWM
		{
			TURN_SERVO_PWM_GPIO->CRL |= (0b10 << 6); // change to alternate function
			TIM2->CCER |= TIM_CCER_CC2E;
		}
		else // 18 ms low voltage
		{
			TURN_SERVO_PWM_GPIO->CRL &= ~(0b11 << 6); // change TURN_SERVO_PWM_PIN to general output
			TURN_SERVO_PWM_GPIO->ODR &= ~(TURN_SERVO_PWM_PIN);
		}

		servoPWM++;
	}
}
