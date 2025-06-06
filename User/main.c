#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_exit.h"
#include "bsp_tim.h"
#include "bsp_fsmc.h"

uint8_t point[]={0x08,0x08,0x08,0x1C,0x14,0x14,0x14,0x36,0x22,0x22,0x42,0x43,0xFF,0xFF,0x00,0x00};/*"未命名文件",0*/

int main(){
	
	USART_Config();
	printf("test begin\n");
	ili9341_init();
	printf("%d",ILI9341_ReadID());
	ili9341_display(0,0,8,16,point);
	while(1){
		key_led();
	}

}
