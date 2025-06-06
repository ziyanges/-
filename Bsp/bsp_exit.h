#ifndef __BSP_EXIT_H__
#define __BSP_EXIT_H__

#include "stm32f10x.h"



#define exit_port GPIOA
#define exit_pin GPIO_Pin_0

#define exit_clk RCC_APB2Periph_GPIOA

void exit_init(void);

#endif
