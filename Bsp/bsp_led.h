#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f10x.h"
#include "bsp_key.h"

#define   LED_PORT_RBG			GPIOB
#define 	LED_CLK 			RCC_APB2Periph_GPIOB
#define   LED_GPIO_MODE  	    GPIO_Mode_Out_PP
#define   LED_GPIO_SPEED	    GPIO_Speed_50MHz

#define     LED_R_PIN				GPIO_Pin_5
#define  	LED_G_PIN				GPIO_Pin_0
#define  	LED_B_PIN				GPIO_Pin_1

#define 	LED_OFF(PIN)  				GPIO_SetBits(    LED_PORT_RBG,PIN)
#define		LED_ON(PIN)						GPIO_ResetBits(LED_PORT_RBG,PIN)
#define		LED_REVERSE(PORT,PIN)	    {PORT->ODR^=PIN;}

void Led_Init(void);
void Led_display(uint8_t mode,FunctionalState NewState);
void key_led(void);

#endif

