#ifndef USART_H_
#define USART_H_

#include <stdio.h>
#include <stdint.h>
#include "system_stm32f10x.h"
#include "stm32f10x.h"

#include "PinDefines.h"

void initializeUSART();

void USARTInterrupt(USART_TypeDef *USARTx);

#endif
