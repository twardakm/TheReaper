#ifndef PINDEFINES_H_
#define PINDEFINES_H_

/*
 * LEDs
 */
#define LED1_GPIO	GPIOC
#define LED1_PIN	GPIO_Pin_14
#define	LED2_GPIO	GPIOC
#define LED2_PIN	GPIO_Pin_15
#define LED3_GPIO	GPIOC
#define LED3_PIN	GPIO_Pin_13
#define LED4_GPIO	GPIOB
#define LED4_PIN	GPIO_Pin_6	//USART1
#define LED5_GPIO	GPIOB
#define LED5_PIN	GPIO_Pin_7	//SysTick
#define LED6_GPIO	GPIOA
#define LED6_PIN	GPIO_Pin_12
#define LED7_GPIO	GPIOA
#define LED7_PIN	GPIO_Pin_11
#define LED8_GPIO	GPIOA
#define LED8_PIN	GPIO_Pin_8
#define LED9_GPIO	GPIOC
#define LED9_PIN	GPIO_Pin_9
#define LED10_GPIO	GPIOC
#define LED10_PIN	GPIO_Pin_8

#define RX_GPIO		GPIOA
#define TX_GPIO		GPIOA
#define RX_PIN		GPIO_Pin_10
#define TX_PIN		GPIO_Pin_9

#define RX2_GPIO	GPIOA
#define TX2_GPIO	GPIOA
#define RX2_PIN		GPIO_Pin_3
#define TX2_PIN		GPIO_Pin_2

#define MOTOR_PWM_GPIO	GPIOA
#define MOTOR_PWM_PIN	GPIO_Pin_0
#define TURN_SERVO_PWM_GPIO	GPIOC
#define TURN_SERVO_PWM_PIN	GPIO_Pin_7

#define MOTOR_DIR_GPIO	GPIOB
#define MOTOR_DIR_PIN	GPIO_Pin_4

#endif
