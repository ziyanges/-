#include "bsp_led.h"


void Led_Init(){
	GPIO_InitTypeDef GpioInitstructure;
	RCC_APB2PeriphClockCmd(LED_CLK,ENABLE);
	
	GpioInitstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GpioInitstructure.GPIO_Speed=GPIO_Speed_50MHz;
	//RED
	
	GpioInitstructure.GPIO_Pin=LED_R_PIN;
	GPIO_Init(LED_PORT_RBG,&GpioInitstructure);
	//GREED
	GpioInitstructure.GPIO_Pin=LED_G_PIN;
	GPIO_Init(LED_PORT_RBG,&GpioInitstructure);
	//BLUE
	GpioInitstructure.GPIO_Pin=LED_B_PIN;
	GPIO_Init(LED_PORT_RBG,&GpioInitstructure);
	
	LED_OFF(LED_R_PIN|LED_G_PIN|LED_B_PIN); 
}


/**
 *@brief	ledµƒœ‘ æ
 *@param  mode:the color will be chose. 
 *    		NewState:color is open or close
 *@retval Œﬁ
 */
void Led_display(uint8_t mode,FunctionalState NewState){
	if(NewState==ENABLE){
		switch(mode){
			case 0: 	LED_ON(LED_R_PIN);break;
			case 1:		LED_ON(LED_B_PIN);break;
			case 2:		LED_ON(LED_G_PIN);break;
		}
	}
	else{
		switch(mode){
			case 0: 	LED_OFF(LED_R_PIN);break;
			case 1:		LED_OFF(LED_B_PIN);break;
			case 2:		LED_OFF(LED_G_PIN);break;
		}
	}
}

void key_led(){
	uint8_t key;
	key=keyScan();
	if(key==1){
		Led_display(0,ENABLE);
	}else if(key==2){
		Led_display(1,ENABLE);
	}
}

