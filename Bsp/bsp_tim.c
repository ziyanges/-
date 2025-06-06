#include "bsp_tim.h"

void tim_init(void){
    //primary timer
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
    TIM_TimeBaseInitTypeDef tim_base_init;
    tim_base_init.TIM_ClockDivision=TIM_CKD_DIV1;
    tim_base_init.TIM_CounterMode=TIM_CounterMode_Up;
    tim_base_init.TIM_Period=10000-1;
    tim_base_init.TIM_Prescaler=7200-1;
    TIM_TimeBaseInit(TIM6,&tim_base_init);
    TIM_ClearFlag(TIM6,TIM_FLAG_Update);
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannel=TIM6_IRQn;
    nvic_init.NVIC_IRQChannelCmd=ENABLE;
    nvic_init.NVIC_IRQChannelPreemptionPriority=0;
    nvic_init.NVIC_IRQChannelSubPriority=0;
    NVIC_Init(&nvic_init);
    TIM_Cmd(TIM6,ENABLE);
}
//end of file

