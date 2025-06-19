#include "bsp_spi_flash.h"
uint16_t spitimeout;
/* 延时函数实现 */
void delay_ms(uint16_t ms)
{
    uint16_t i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<9000;j++);  // stm32f103vet6在72MHz时钟下,大约1ms延时
}

u8 SPI_TIMEOUT_UserCallback(uint16_t parameter){
	printf("超时\n");
	return 0;
}


void SPI_flash_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_6 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	SPI_flash_CS_HIGH();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);

	SPI_Cmd(SPI1, ENABLE);
}

//发送一个字节
u8 SPI_flash_SendByte(uint8_t byte){
	spitimeout = 0xFFFF;
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){
		if((spitimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
	}
	SPI_I2S_SendData(SPI1, byte);
	spitimeout = 0xFFFF;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
	{
		if((spitimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
	}
	return SPI_I2S_ReceiveData(SPI1);
}

//接收一个字节
u8 SPI_flash_ReadByte(void){
	return SPI_flash_SendByte(dummy_byte);
}

void SPI_flash_readDeviceId(){
	uint8_t id[3];
	SPI_flash_CS_LOW();
	SPI_flash_SendByte(JEDEC_ID);
	id[0] = SPI_flash_SendByte(dummy_byte);
	id[1] = SPI_flash_SendByte(dummy_byte);
	id[2] = SPI_flash_SendByte(dummy_byte);
	SPI_flash_CS_HIGH();
	printf("flash id: 0x%x 0x%x 0x%x\n", id[0], id[1], id[2]);
}

void spi_flash_write_enable(){
	SPI_flash_CS_LOW();
	SPI_flash_SendByte(W25X_WriteEnable);
	SPI_flash_CS_HIGH();
}

void spi_flash_wait_busy(){
	uint8_t status;
	do{
		SPI_flash_CS_LOW();
		SPI_flash_SendByte(W25X_ReadStatusReg);
		status = SPI_flash_ReadByte();
		SPI_flash_CS_HIGH();
	}while(status & 0x01);
}

void spi_flash_buffer_Read(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead){
	SPI_flash_CS_LOW();
	SPI_flash_SendByte(W25X_ReadData);
	SPI_flash_SendByte((uint8_t)((ReadAddr) >> 16));
	SPI_flash_SendByte((uint8_t)((ReadAddr) >> 8));
	SPI_flash_SendByte((uint8_t)ReadAddr);
	while(NumByteToRead--){
		*pBuffer = SPI_flash_ReadByte();
		pBuffer++;
	}
	SPI_flash_CS_HIGH();
}
