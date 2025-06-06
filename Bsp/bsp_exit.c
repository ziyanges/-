#include "bsp_exit.h"

void set_NVIC(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef nvic_init;
	nvic_init.NVIC_IRQChannel=EXTI0_IRQn;
	nvic_init.NVIC_IRQChannelCmd=ENABLE;
	nvic_init.NVIC_IRQChannelPreemptionPriority=0;
	nvic_init.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvic_init);
}

void exit_init(void){
	set_NVIC();
	GPIO_InitTypeDef exit_gpio_init;
	EXTI_InitTypeDef exti_init;
	//CONFIG EXIT CLK
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);

	exit_gpio_init.GPIO_Mode=GPIO_Mode_IPU;
	exit_gpio_init.GPIO_Pin=exit_pin;
	GPIO_Init(exit_port,&exit_gpio_init);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, exit_pin);

	exti_init.EXTI_Line=EXTI_Line0;
	exti_init.EXTI_LineCmd=ENABLE;
	exti_init.EXTI_Mode=EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&exti_init);
}
