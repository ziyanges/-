#ifndef __BSP_FSMC_H__
#define __BSP_FSMC_H__

#include "stm32f10x.h"

#define peripheral_address 0x60000000
#define DATA (peripheral_address|(0x1<<17))
#define CMD  (peripheral_address|(0x0<<17))

#define      WHITE		 		           0xFFFF	   //白色
#define      BLACK                         0x0000	   //黑色

/******************************* 定义 ILI934 常用命令 ********************************/
#define      CMD_SetCoordinateX		 		    0x2A	     //设置X坐标
#define      CMD_SetCoordinateY		 		    0x2B	     //设置Y坐标
#define      CMD_SetPixel		 		        0x2C	     //填充像素

/*************************************** 调试预用 ******************************************/
#define      DEBUG_DELAY()   


/******************************* ILI9341 显示屏8080通讯引脚定义 ***************************/
/******控制信号线******/
//片选，选择NOR/SRAM块
#define      ILI9341_CS_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_CS_PORT               GPIOD
#define      ILI9341_CS_PIN                GPIO_Pin_7

//DC引脚，使用FSMC的地址信号控制，本引脚决定了访问LCD时使用的地址
//PD11为FSMC_A16
#define      ILI9341_DC_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_DC_PORT               GPIOD
#define      ILI9341_DC_PIN                GPIO_Pin_11

//写使能
#define      ILI9341_WR_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_WR_PORT               GPIOD
#define      ILI9341_WR_PIN                GPIO_Pin_5

//读使能
#define      ILI9341_RD_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_RD_PORT               GPIOD
#define      ILI9341_RD_PIN                GPIO_Pin_4

//复位引脚
#define      ILI9341_RST_CLK               RCC_APB2Periph_GPIOE
#define      ILI9341_RST_PORT              GPIOE
#define      ILI9341_RST_PIN               GPIO_Pin_1

//背光引脚
#define      ILI9341_BK_CLK                RCC_APB2Periph_GPIOD    
#define      ILI9341_BK_PORT               GPIOD
#define      ILI9341_BK_PIN                GPIO_Pin_12

/********数据信号线***************/
#define      ILI9341_D0_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D0_PORT               GPIOD
#define      ILI9341_D0_PIN                GPIO_Pin_14

#define      ILI9341_D1_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D1_PORT               GPIOD
#define      ILI9341_D1_PIN                GPIO_Pin_15

#define      ILI9341_D2_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D2_PORT               GPIOD
#define      ILI9341_D2_PIN                GPIO_Pin_0

#define      ILI9341_D3_CLK                RCC_APB2Periph_GPIOD  
#define      ILI9341_D3_PORT               GPIOD
#define      ILI9341_D3_PIN                GPIO_Pin_1

#define      ILI9341_D4_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D4_PORT               GPIOE
#define      ILI9341_D4_PIN                GPIO_Pin_7

#define      ILI9341_D5_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D5_PORT               GPIOE
#define      ILI9341_D5_PIN                GPIO_Pin_8

#define      ILI9341_D6_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D6_PORT               GPIOE
#define      ILI9341_D6_PIN                GPIO_Pin_9

#define      ILI9341_D7_CLK                RCC_APB2Periph_GPIOE  
#define      ILI9341_D7_PORT               GPIOE
#define      ILI9341_D7_PIN                GPIO_Pin_10

#define      ILI9341_D8_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D8_PORT               GPIOE
#define      ILI9341_D8_PIN                GPIO_Pin_11

#define      ILI9341_D9_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D9_PORT               GPIOE
#define      ILI9341_D9_PIN                GPIO_Pin_12

#define      ILI9341_D10_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D10_PORT               GPIOE
#define      ILI9341_D10_PIN                GPIO_Pin_13

#define      ILI9341_D11_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D11_PORT               GPIOE
#define      ILI9341_D11_PIN                GPIO_Pin_14

#define      ILI9341_D12_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D12_PORT               GPIOE
#define      ILI9341_D12_PIN                GPIO_Pin_15

#define      ILI9341_D13_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D13_PORT               GPIOD
#define      ILI9341_D13_PIN                GPIO_Pin_8

#define      ILI9341_D14_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D14_PORT               GPIOD
#define      ILI9341_D14_PIN                GPIO_Pin_9

#define      ILI9341_D15_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D15_PORT               GPIOD
#define      ILI9341_D15_PIN                GPIO_Pin_10

#define 			ILI9341_LESS_PIXEL	  							240			//液晶屏较短方向的像素宽度
#define 			ILI9341_MORE_PIXEL	 								320			//液晶屏较长方向的像素宽度

/* 定义 LCD 驱动芯片 ID */
#define     LCDID_UNKNOWN             0
#define     LCDID_ILI9341             0x9341
#define     LCDID_ST7789V             0x8552

//function of ILI9341
void ili9341_init(void);
uint16_t ILI9341_ReadID(void);
void ili9341_display(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t *point);


#endif
