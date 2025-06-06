#include  "bsp_key.h"

void key_gpio_init(){
	GPIO_InitTypeDef keyInitStructure;
	RCC_APB2PeriphClockCmd(KEY1_CLK|KEY2_CLK,ENABLE);
	
	//KEY1
	keyInitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	keyInitStructure.GPIO_Pin=KEY1_PIN;
	GPIO_Init(KEY1_PORT, &keyInitStructure);
	//KEY2
	keyInitStructure.GPIO_Pin=KEY2_PIN;
	keyInitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY2_PORT, &keyInitStructure);
}


uint8_t keyScan(){
	if(GPIO_ReadInputDataBit(KEY1_PORT,KEY1_PIN)==0||GPIO_ReadInputDataBit(KEY2_PORT,KEY2_PIN)==0){
		if(GPIO_ReadInputDataBit(KEY1_PORT,KEY1_PIN)==1) return KEY1_ON;
		if(GPIO_ReadInputDataBit(KEY2_PORT,KEY2_PIN)==1) return KEY2_ON;
	}
	return 0;
}
