#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_exit.h"
#include "bsp_tim.h"
#include "bsp_fsmc.h"
#include "bsp_tim_pwm.h"
#include "bsp_spi_flash.h"

uint16_t indexWave[] = {
    1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4,
    4, 5, 5, 6, 7, 8, 9, 10, 11, 13,
    15, 17, 19, 22, 25, 28, 32, 36,
    41, 47, 53, 61, 69, 79, 89, 102,
    116, 131, 149, 170, 193, 219, 250,
    284, 323, 367, 417, 474, 539, 613,
    697, 792, 901, 1022, 1022, 901, 792,
    697, 613, 539, 474, 417, 367, 323,
    284, 250, 219, 193, 170, 149, 131, 
    116, 102, 89, 79, 69, 61, 53, 47, 41,
    36, 32, 28, 25, 22, 19, 17, 15, 13, 
    11, 10, 9, 8, 7, 6, 5, 5, 4, 4, 3, 3,
    2, 2, 2, 2, 1, 1, 1, 1
        
    };

//计算PWM表有多少个元素
uint16_t POINT_NUM = sizeof(indexWave)/sizeof(indexWave[0]); 
		

uint8_t point[]={0x08,0x08,0x08,0x1C,0x14,0x14,0x14,0x36,0x22,0x22,0x42,0x43,0xFF,0xFF,0x00,0x00};/*"未命名文件",0*/

// int main(){
// 	uint16_t pwm_index = 0;			//用于PWM查表
    
//     // 系统初始化
//     USART_Config();
//     printf("PWM Test Started\n");
    
//     // 初始化PWM输出
//     TIM_PWM_Init();
    
//     // 主循环
//     while (1) {
//         if( pwm_index >=  POINT_NUM)			
// 				{
// 					pwm_index=0;								
// 				}
// 		tim_pwm_set(indexWave[pwm_index++]);
// 		printf("pwm_index=%d\n",indexWave[pwm_index]);
//         // 输出PWM占空比
        
//         // 延时10ms，使PWM变化更平滑
//         delay_ms(50);
//     }

// }


int main(){
    USART_Config();
    printf("flash Test Started\n");
    SPI_flash_Init();
    delay_ms(50);
    SPI_flash_readDeviceId();

}
