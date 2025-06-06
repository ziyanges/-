#ifndef __BSP_USART_H__
#define __BSP_USART_H__

#include "stm32f10x.h"
#include <stdio.h>

#define 		USART1_GPIO_CLK 			RCC_APB2Periph_GPIOA
//TX
#define			TX_MODE					GPIO_Mode_AF_PP
#define			TX_SPEED				GPIO_Speed_50MHz
#define  		TX_PIN					GPIO_Pin_9 
#define			TX_PORT					GPIOA

//RX
#define			RX_MODE					GPIO_Mode_IN_FLOATING
#define			RX_PIN					GPIO_Pin_10
#define			RX_PORT					GPIOA

#define			USART1_CLK			RCC_APB2Periph_USART1
#define 		USARTx          USART1

void USART_Config(void);


#endif

