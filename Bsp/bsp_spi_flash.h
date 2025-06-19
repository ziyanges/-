#ifndef __BSP_SPI_flash_H__
#define __BSP_SPI_flash_H__


#include "stm32f10x.h"
#include "bsp_usart.h"
                                /*相关命令 */
#define dummy_byte  0xff
#define W25X_WriteEnable       0x06
#define W25X_WriteDisable      0x04
#define JEDEC_ID    0x9f
#define W25X_ReadStatusReg     0x05
#define W25X_WriteStatusReg    0x01
#define W25X_ReadData          0x03


#define W25Q80 0x178058

#define SPI_flash_CS_LOW()      GPIO_ResetBits(GPIOC,GPIO_Pin_0)
#define SPI_flash_CS_HIGH()     GPIO_SetBits(GPIOC,GPIO_Pin_0)

                            /*函数申明*/
void SPI_flash_Init(void);
uint8_t SPI_flash_SendByte(uint8_t byte);
uint8_t SPI_flash_ReadByte(void);
void SPI_flash_readDeviceId(void);
void spi_flash_write_enable(void);
void spi_flash_wait_busy(void);
void spi_flash_buffer_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);

#endif
