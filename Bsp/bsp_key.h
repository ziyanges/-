#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "stm32f10x.h"

#define 			KEY1_ON 			1
#define				KEY2_ON				2

//key1
#define       KEY1_CLK			RCC_APB2Periph_GPIOA
#define				KEY1_PIN			GPIO_Pin_0
#define  			KEY1_PORT			GPIOA

//KEYH2
#define       KEY2_CLK			RCC_APB2Periph_GPIOC
#define				KEY2_PIN			GPIO_Pin_13
#define  			KEY2_PORT			GPIOC

void 				key_gpio_init(void);
uint8_t 		keyScan(void);




#endif


