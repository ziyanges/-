#include "bsp_tim_pwm.h"

void TIM_PWM_Init(){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    // 启用AFIO时钟（若使用重映射功能）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 若需要部分重映射TIM3（将CH2映射到PB5）
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_TimeBaseInitStructure.TIM_Period=(1024-1);
    TIM_TimeBaseInitStructure.TIM_Prescaler=(200-1);
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
    TIM_Cmd(TIM3,ENABLE);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState=TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_Pulse=0;
    TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;
    TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset;
    
    TIM_OC2Init(TIM3,&TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
    // 使能自动重装载,缓冲作用
    TIM_ARRPreloadConfig(TIM3, ENABLE);
}

void tim_pwm_set(int value){
    TIM3->CCR2 = value;
}



