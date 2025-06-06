#include "bsp_fsmc.h"
//根据液晶扫描方向而变化的XY像素宽度
//调用ILI9341_GramScan函数设置方向时会自动更改
uint16_t LCD_X_LENGTH = ILI9341_LESS_PIXEL;
uint16_t LCD_Y_LENGTH = ILI9341_MORE_PIXEL;

static uint16_t CurrentTextColor   = BLACK;//前景色
static uint16_t CurrentBackColor   = WHITE;//背景色

//设置扫描方向
uint8_t LCD_SCAN_MODE = 6;

//保存液晶屏驱动ic的 ID
uint16_t lcdid = LCDID_UNKNOWN;

static void ILI9341_Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}

void LCD_GPIO_init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    /* 使能FSMC对应相应管脚时钟*/
	RCC_APB2PeriphClockCmd ( 	
        /*控制信号*/
        ILI9341_CS_CLK|ILI9341_DC_CLK|ILI9341_WR_CLK|
        ILI9341_RD_CLK	|ILI9341_BK_CLK|ILI9341_RST_CLK|
        /*数据信号*/
        ILI9341_D0_CLK|ILI9341_D1_CLK|	ILI9341_D2_CLK | 
        ILI9341_D3_CLK | ILI9341_D4_CLK|ILI9341_D5_CLK|
        ILI9341_D6_CLK | ILI9341_D7_CLK|ILI9341_D8_CLK|
        ILI9341_D9_CLK | ILI9341_D10_CLK|ILI9341_D11_CLK|
        ILI9341_D12_CLK | ILI9341_D13_CLK|ILI9341_D14_CLK|
        ILI9341_D15_CLK	, ENABLE );
    /* 配置FSMC相对应的数据线,FSMC-D0~D15 */	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D0_PIN;
	GPIO_Init ( ILI9341_D0_PORT, & GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = ILI9341_D1_PIN;
	GPIO_Init ( ILI9341_D1_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D2_PIN;
	GPIO_Init ( ILI9341_D2_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D3_PIN;
	GPIO_Init ( ILI9341_D3_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D4_PIN;
	GPIO_Init ( ILI9341_D4_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D5_PIN;
	GPIO_Init ( ILI9341_D5_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D6_PIN;
	GPIO_Init ( ILI9341_D6_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D7_PIN;
	GPIO_Init ( ILI9341_D7_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D8_PIN;
	GPIO_Init ( ILI9341_D8_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D9_PIN;
	GPIO_Init ( ILI9341_D9_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D10_PIN;
	GPIO_Init ( ILI9341_D10_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D11_PIN;
	GPIO_Init ( ILI9341_D11_PORT, & GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = ILI9341_D12_PIN;
	GPIO_Init ( ILI9341_D12_PORT, & GPIO_InitStructure );	
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D13_PIN;
	GPIO_Init ( ILI9341_D13_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D14_PIN;
	GPIO_Init ( ILI9341_D14_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_D15_PIN;
	GPIO_Init ( ILI9341_D15_PORT, & GPIO_InitStructure );

    /* 配置FSMC相对应的控制线
	 * FSMC_NOE   :LCD-RD
	 * FSMC_NWE   :LCD-WR
	 * FSMC_NE1   :LCD-CS
	 * FSMC_A16   :LCD-DC
	 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_RD_PIN; 
	GPIO_Init (ILI9341_RD_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_WR_PIN; 
	GPIO_Init (ILI9341_WR_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_CS_PIN; 
	GPIO_Init ( ILI9341_CS_PORT, & GPIO_InitStructure );  
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_DC_PIN; 
	GPIO_Init ( ILI9341_DC_PORT, & GPIO_InitStructure );
	
     /* 配置LCD复位RST控制管脚*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_RST_PIN; 
	GPIO_Init ( ILI9341_RST_PORT, & GPIO_InitStructure );
	
	/* 配置LCD背光控制管脚BK*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_BK_PIN; 
	GPIO_Init ( ILI9341_BK_PORT, & GPIO_InitStructure );
}

void FSMC_config(void){
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStruct;
    FSMC_NORSRAMTimingInitTypeDef FSMC_WriteTimingStruct;
    /* 使能FSMC时钟*/
    RCC_AHBPeriphClockCmd ( RCC_AHBPeriph_FSMC, ENABLE );
    FSMC_ReadWriteTimingStruct.FSMC_AddressSetupTime = 0x01;
    FSMC_ReadWriteTimingStruct.FSMC_AddressHoldTime = 0x00;
    FSMC_ReadWriteTimingStruct.FSMC_DataSetupTime = 0x05;
    FSMC_ReadWriteTimingStruct.FSMC_BusTurnAroundDuration = 0x00;
    FSMC_ReadWriteTimingStruct.FSMC_CLKDivision = 0x00;
    FSMC_WriteTimingStruct.FSMC_DataLatency=0x00;
    FSMC_WriteTimingStruct.FSMC_AccessMode=FSMC_AccessMode_B;
    //read and write timing are the same
    FSMC_ReadWriteTimingStruct=FSMC_WriteTimingStruct;

    /* 配置FSMC为NOR/SRAM模式*/ 
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteTimingStruct;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_WriteTimingStruct;
    /* 初始化FSMC */
    FSMC_NORSRAMInit ( &FSMC_NORSRAMInitStructure );
    /* 使能FSMC_Bank1_NORSRAM1*/
    FSMC_NORSRAMCmd ( FSMC_Bank1_NORSRAM1, ENABLE );
}

//write data
void ILI9341_Write_Data(u16 data){
    *(__IO uint16_t *)(DATA)=data;
}

//write command
void ILI9341_Write_Cmd(u8 cmd){
	*(__IO uint16_t *)(CMD)=cmd;
}

u16 read_from_ili9341(){
	u16 data;
	data=*(__IO uint16_t *)(DATA);
    return data;	//return the value of the pointe
}

uint16_t ILI9341_ReadID(void){
    uint16_t id = 0;
    ILI9341_Write_Cmd(0x04);
    read_from_ili9341();
    read_from_ili9341();
    id = read_from_ili9341();
    id=id<<8;
    id |= read_from_ili9341();
    if(id==LCDID_ST7789V){
        return id;
    }else{
        ILI9341_Write_Cmd(0xD3);
        read_from_ili9341();
        read_from_ili9341();
        id = read_from_ili9341();
        id=id<<8;
        id |= read_from_ili9341();
        if (id==LCDID_ILI9341){
            return id;
        }
    }
    return LCDID_UNKNOWN;
}



/**
 * @brief  初始化ILI9341寄存器
 * @param  无
 * @retval 无
 */
static void ILI9341_REG_Config ( void )
{
  lcdid = ILI9341_ReadID();
  
  if(lcdid == LCDID_ILI9341)
  {
    /*  Power control B (CFh)  */
    DEBUG_DELAY  ();
    ILI9341_Write_Cmd ( 0xCF  );
    ILI9341_Write_Data ( 0x00  );
    ILI9341_Write_Data ( 0x81  );
    ILI9341_Write_Data ( 0x30  );
    
    /*  Power on sequence control (EDh) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xED );
    ILI9341_Write_Data ( 0x64 );
    ILI9341_Write_Data ( 0x03 );
    ILI9341_Write_Data ( 0x12 );
    ILI9341_Write_Data ( 0x81 );
    
    /*  Driver timing control A (E8h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xE8 );
    ILI9341_Write_Data ( 0x85 );
    ILI9341_Write_Data ( 0x10 );
    ILI9341_Write_Data ( 0x78 );
    
    /*  Power control A (CBh) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xCB );
    ILI9341_Write_Data ( 0x39 );
    ILI9341_Write_Data ( 0x2C );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x34 );
    //ILI9341_Write_Data ( 0x02 );
    ILI9341_Write_Data ( 0x06 ); //原来是0x02改为0x06可防止液晶显示白屏时有条纹的情况
    
    /* Pump ratio control (F7h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xF7 );
    ILI9341_Write_Data ( 0x20 );
    
    /* Driver timing control B */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xEA );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x00 );
    
    /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xB1 );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x1B );
    
    /*  Display Function Control (B6h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xB6 );
    ILI9341_Write_Data ( 0x0A );
    ILI9341_Write_Data ( 0xA2 );
    
    /* Power Control 1 (C0h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xC0 );
    ILI9341_Write_Data ( 0x35 );
    
    /* Power Control 2 (C1h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xC1 );
    ILI9341_Write_Data ( 0x11 );
    
    /* VCOM Control 1 (C5h) */
    ILI9341_Write_Cmd ( 0xC5 );
    ILI9341_Write_Data ( 0x45 );
    ILI9341_Write_Data ( 0x45 );
    
    /*  VCOM Control 2 (C7h)  */
    ILI9341_Write_Cmd ( 0xC7 );
    ILI9341_Write_Data ( 0xA2 );
    
    /* Enable 3G (F2h) */
    ILI9341_Write_Cmd ( 0xF2 );
    ILI9341_Write_Data ( 0x00 );
    
    /* Gamma Set (26h) */
    ILI9341_Write_Cmd ( 0x26 );
    ILI9341_Write_Data ( 0x01 );
    DEBUG_DELAY ();
    
    /* Positive Gamma Correction */
    ILI9341_Write_Cmd ( 0xE0 ); //Set Gamma
    ILI9341_Write_Data ( 0x0F );
    ILI9341_Write_Data ( 0x26 );
    ILI9341_Write_Data ( 0x24 );
    ILI9341_Write_Data ( 0x0B );
    ILI9341_Write_Data ( 0x0E );
    ILI9341_Write_Data ( 0x09 );
    ILI9341_Write_Data ( 0x54 );
    ILI9341_Write_Data ( 0xA8 );
    ILI9341_Write_Data ( 0x46 );
    ILI9341_Write_Data ( 0x0C );
    ILI9341_Write_Data ( 0x17 );
    ILI9341_Write_Data ( 0x09 );
    ILI9341_Write_Data ( 0x0F );
    ILI9341_Write_Data ( 0x07 );
    ILI9341_Write_Data ( 0x00 );
    
    /* Negative Gamma Correction (E1h) */
    ILI9341_Write_Cmd ( 0XE1 ); //Set Gamma
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x19 );
    ILI9341_Write_Data ( 0x1B );
    ILI9341_Write_Data ( 0x04 );
    ILI9341_Write_Data ( 0x10 );
    ILI9341_Write_Data ( 0x07 );
    ILI9341_Write_Data ( 0x2A );
    ILI9341_Write_Data ( 0x47 );
    ILI9341_Write_Data ( 0x39 );
    ILI9341_Write_Data ( 0x03 );
    ILI9341_Write_Data ( 0x06 );
    ILI9341_Write_Data ( 0x06 );
    ILI9341_Write_Data ( 0x30 );
    ILI9341_Write_Data ( 0x38 );
    ILI9341_Write_Data ( 0x0F );
    
    /* memory access control set */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0x36 ); 	
    ILI9341_Write_Data ( 0xC8 );    /*竖屏  左上角到 (起点)到右下角 (终点)扫描方式*/
    DEBUG_DELAY ();
    
    /* column address control set */
    ILI9341_Write_Cmd ( CMD_SetCoordinateX ); 
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0xEF );
    
    /* page address control set */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( CMD_SetCoordinateY ); 
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x01 );
    ILI9341_Write_Data ( 0x3F );
    
    /*  Pixel Format Set (3Ah)  */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0x3a ); 
    ILI9341_Write_Data ( 0x55 );
    
    /* Sleep Out (11h)  */
    ILI9341_Write_Cmd ( 0x11 );	
    ILI9341_Delay ( 0xAFFf<<2 );
    DEBUG_DELAY ();
    
    /* Display ON (29h) */
    ILI9341_Write_Cmd ( 0x29 ); 
	}
  
  else if(lcdid == LCDID_ST7789V)
  {
    /*  Power control B (CFh)  */
    DEBUG_DELAY  ();
    ILI9341_Write_Cmd ( 0xCF  );
    ILI9341_Write_Data ( 0x00  );
    ILI9341_Write_Data ( 0xC1  );
    ILI9341_Write_Data ( 0x30  );
    
    /*  Power on sequence control (EDh) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xED );
    ILI9341_Write_Data ( 0x64 );
    ILI9341_Write_Data ( 0x03 );
    ILI9341_Write_Data ( 0x12 );
    ILI9341_Write_Data ( 0x81 );
    
    /*  Driver timing control A (E8h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xE8 );
    ILI9341_Write_Data ( 0x85 );
    ILI9341_Write_Data ( 0x10 );
    ILI9341_Write_Data ( 0x78 );
    
    /*  Power control A (CBh) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xCB );
    ILI9341_Write_Data ( 0x39 );
    ILI9341_Write_Data ( 0x2C );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x34 );
    ILI9341_Write_Data ( 0x02 );
    
    /* Pump ratio control (F7h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xF7 );
    ILI9341_Write_Data ( 0x20 );
    
    /* Driver timing control B */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xEA );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x00 );
    
    
    /* Power Control 1 (C0h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xC0 );   //Power control
    ILI9341_Write_Data ( 0x21 );  //VRH[5:0]
    
    /* Power Control 2 (C1h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xC1 );   //Power control
    ILI9341_Write_Data ( 0x11 );  //SAP[2:0];BT[3:0]
    
    /* VCOM Control 1 (C5h) */
    ILI9341_Write_Cmd ( 0xC5 );
    ILI9341_Write_Data ( 0x2D );
    ILI9341_Write_Data ( 0x33 );
    
    /*  VCOM Control 2 (C7h)  */
//	ILI9341_Write_Cmd ( 0xC7 );
//	ILI9341_Write_Data ( 0XC0 );
    
    /* memory access control set */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0x36 );   //Memory Access Control
    ILI9341_Write_Data ( 0x00 );  /*竖屏  左上角到 (起点)到右下角 (终点)扫描方式*/
    DEBUG_DELAY ();
    
    ILI9341_Write_Cmd(0x3A);   
    ILI9341_Write_Data(0x55); 
    
      /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xB1 );
    ILI9341_Write_Data ( 0x00 );
    ILI9341_Write_Data ( 0x17 );
    
    /*  Display Function Control (B6h) */
    DEBUG_DELAY ();
    ILI9341_Write_Cmd ( 0xB6 );
    ILI9341_Write_Data ( 0x0A );
    ILI9341_Write_Data ( 0xA2 );
    
    ILI9341_Write_Cmd(0xF6);    			
    ILI9341_Write_Data(0x01); 
    ILI9341_Write_Data(0x30); 
    
    /* Enable 3G (F2h) */
    ILI9341_Write_Cmd ( 0xF2 );
    ILI9341_Write_Data ( 0x00 );
    
    /* Gamma Set (26h) */
    ILI9341_Write_Cmd ( 0x26 );
    ILI9341_Write_Data ( 0x01 );
    DEBUG_DELAY ();
    
    /* Positive Gamma Correction */
    ILI9341_Write_Cmd(0xe0); //Positive gamma
    ILI9341_Write_Data(0xd0);         
    ILI9341_Write_Data(0x00); 
    ILI9341_Write_Data(0x02); 
    ILI9341_Write_Data(0x07); 
    ILI9341_Write_Data(0x0b); 
    ILI9341_Write_Data(0x1a); 
    ILI9341_Write_Data(0x31); 
    ILI9341_Write_Data(0x54); 
    ILI9341_Write_Data(0x40); 
    ILI9341_Write_Data(0x29); 
    ILI9341_Write_Data(0x12); 
    ILI9341_Write_Data(0x12); 
    ILI9341_Write_Data(0x12); 
    ILI9341_Write_Data(0x17);

    /* Negative Gamma Correction (E1h) */
    ILI9341_Write_Cmd(0xe1); //Negative gamma
    ILI9341_Write_Data(0xd0); 
    ILI9341_Write_Data(0x00); 
    ILI9341_Write_Data(0x02); 
    ILI9341_Write_Data(0x07); 
    ILI9341_Write_Data(0x05); 
    ILI9341_Write_Data(0x25); 
    ILI9341_Write_Data(0x2d); 
    ILI9341_Write_Data(0x44); 
    ILI9341_Write_Data(0x45); 
    ILI9341_Write_Data(0x1c); 
    ILI9341_Write_Data(0x18); 
    ILI9341_Write_Data(0x16); 
    ILI9341_Write_Data(0x1c); 
    ILI9341_Write_Data(0x1d); 
  
	
//	/* column address control set */
//	ILI9341_Write_Cmd ( CMD_SetCoordinateX ); 
//	ILI9341_Write_Data ( 0x00 );
//	ILI9341_Write_Data ( 0x00 );
//	ILI9341_Write_Data ( 0x00 );
//	ILI9341_Write_Data ( 0xEF );
//	
//	/* page address control set */
//	DEBUG_DELAY ();
//	ILI9341_Write_Cmd ( CMD_SetCoordinateY ); 
//	ILI9341_Write_Data ( 0x00 );
//	ILI9341_Write_Data ( 0x00 );
//	ILI9341_Write_Data ( 0x01 );
//	ILI9341_Write_Data ( 0x3F );
	
    /* Sleep Out (11h)  */
    ILI9341_Write_Cmd ( 0x11 );	  //Exit Sleep
    ILI9341_Delay ( 0xAFFf<<2 );
    DEBUG_DELAY ();
    
    /* Display ON (29h) */
    ILI9341_Write_Cmd ( 0x29 );   //Display on
    
    ILI9341_Write_Cmd(0x2c);
  }	
}

//open backlight
void ILI9341_BackLed_Control ( FunctionalState enumState )
{
	if ( enumState )
		GPIO_ResetBits ( ILI9341_BK_PORT, ILI9341_BK_PIN );	
	else
		GPIO_SetBits ( ILI9341_BK_PORT, ILI9341_BK_PIN );
}

//reset
void ILI9341_Rst ( void )
{			
	GPIO_ResetBits ( ILI9341_RST_PORT, ILI9341_RST_PIN );	 //低电平复位

	ILI9341_Delay ( 0xAFF ); 					   

	GPIO_SetBits ( ILI9341_RST_PORT, ILI9341_RST_PIN );		 	 

	ILI9341_Delay ( 0xAFF ); 	
	
}

void ILI9341_GramScan ( uint8_t ucOption )
{	
	//参数检查，只可输入0-7
	if(ucOption >7 )
		return;
	
	//根据模式更新LCD_SCAN_MODE的值，主要用于触摸屏选择计算参数
	LCD_SCAN_MODE = ucOption;
	
	//根据模式更新XY方向的像素宽度
	if(ucOption%2 == 0)	
	{
		//0 2 4 6模式下X方向像素宽度为240，Y方向为320
		LCD_X_LENGTH = ILI9341_LESS_PIXEL;
		LCD_Y_LENGTH =	ILI9341_MORE_PIXEL;
	}
	else				
	{
		//1 3 5 7模式下X方向像素宽度为320，Y方向为240
		LCD_X_LENGTH = ILI9341_MORE_PIXEL;
		LCD_Y_LENGTH =	ILI9341_LESS_PIXEL; 
	}

	//0x36命令参数的高3位可用于设置GRAM扫描方向	
	ILI9341_Write_Cmd ( 0x36 );
  if(lcdid == LCDID_ILI9341)
  {
    ILI9341_Write_Data ( 0x08 |(ucOption<<5));//根据ucOption的值设置LCD参数，共0-7种模式
  }
  else if(lcdid == LCDID_ST7789V)
  {
    ILI9341_Write_Data ( 0x00 |(ucOption<<5));//根据ucOption的值设置LCD参数，共0-7种模式
  }
	ILI9341_Write_Cmd ( CMD_SetCoordinateX ); 
	ILI9341_Write_Data ( 0x00 );		/* x 起始坐标高8位 */
	ILI9341_Write_Data ( 0x00 );		/* x 起始坐标低8位 */
	ILI9341_Write_Data ( ((LCD_X_LENGTH-1)>>8)&0xFF ); /* x 结束坐标高8位 */	
	ILI9341_Write_Data ( (LCD_X_LENGTH-1)&0xFF );				/* x 结束坐标低8位 */

	ILI9341_Write_Cmd ( CMD_SetCoordinateY ); 
	ILI9341_Write_Data ( 0x00 );		/* y 起始坐标高8位 */
	ILI9341_Write_Data ( 0x00 );		/* y 起始坐标低8位 */
	ILI9341_Write_Data ( ((LCD_Y_LENGTH-1)>>8)&0xFF );	/* y 结束坐标高8位 */	 
	ILI9341_Write_Data ( (LCD_Y_LENGTH-1)&0xFF );				/* y 结束坐标低8位 */

	/* write gram start */
	ILI9341_Write_Cmd ( CMD_SetPixel );	
}


void ili9341_init(void){
	LCD_GPIO_init();
    FSMC_config();
    ILI9341_BackLed_Control ( ENABLE );      //点亮LCD背光灯
    ILI9341_Rst ();
    ILI9341_REG_Config();
    ILI9341_GramScan(LCD_SCAN_MODE);
}


void ili9341_display(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t *data){
	ILI9341_Write_Cmd(0x2A);
    ILI9341_Write_Data(x>>8);
    ILI9341_Write_Data(x);
    ILI9341_Write_Data((x+width-1)>>8);
    ILI9341_Write_Data((x+width-1));
    ILI9341_Write_Cmd(0x2B);
    ILI9341_Write_Data(y>>8);
    ILI9341_Write_Data(y);
    ILI9341_Write_Data((y+height-1)>>8);
    ILI9341_Write_Data((y+height-1));
    ILI9341_Write_Cmd(0x2C);
    for(int i=0;i<width*height/8;i++){
        for(int j=0;j<8;j++){
            if(((data[i])&(1<<j))!=0){
                ILI9341_Write_Data(0xF800);
            }else{
                ILI9341_Write_Data(0x0000);
            }
        }
    }
}


