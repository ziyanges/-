#include "bsp_usart.h"

void USART_gpioInit(){
	GPIO_InitTypeDef GpioInitstructure;
	RCC_APB2PeriphClockCmd(USART1_GPIO_CLK,ENABLE);
	//TX
	GpioInitstructure.GPIO_Mode=TX_MODE;
	GpioInitstructure.GPIO_Pin=TX_PIN;
	GpioInitstructure.GPIO_Speed=TX_SPEED;
	GPIO_Init(TX_PORT,&GpioInitstructure);
	//RX
	GpioInitstructure.GPIO_Mode=RX_MODE;
	GpioInitstructure.GPIO_Pin=RX_PIN;
	GPIO_Init(RX_PORT,&GpioInitstructure);
}


void USART_Config(){
	USART_gpioInit();
	USART_InitTypeDef  USART_Structure;
	RCC_APB2PeriphClockCmd(USART1_CLK,ENABLE);
	
	USART_Structure.USART_BaudRate=115200;
	USART_Structure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_Structure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Structure.USART_Parity=USART_Parity_No;
	USART_Structure.USART_StopBits=USART_StopBits_1;
	USART_Structure.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USARTx,&USART_Structure);
	USART_Cmd(USARTx,ENABLE);
}

int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口DEBUG_USART */
    USART_SendData(USARTx,(uint8_t)ch);  
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
    return (ch);
}

int fgetc(FILE *f){
	 while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
	 return (int)USART_ReceiveData(USARTx); 
}


