/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_AD9851.c
* @Description : None
* @Date        : 2016/7/20
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     :  
-------------------------------------------------------------------------------
频率换算为频率字系数
由计算公式：Fout=(Freq*AD9851_SystemCloc)/2^32 Freq 为频率控制字
得 Freq=FC*Fout
FC=2^32/AD9851_SystemCloc
当AD9851_SystemCloc=30MHz
时 FC=143.16557653333333333333333333333f 
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_AD9851.h"							

/* 私有宏定义 ----------------------------------------------------------------*/ 
#define M20				 				214.7483648f
#define M30							 	143.16557653333333333333333333333f 
#define M50 							85.89934592f
#define M120							35.791394133333333333333333333333f 

#define MULT 							0  //6倍频  	0关闭，1打开
#define POWER_MODE 						0 //功耗模式 0：Power-up_ mode 1:Power-down_ 
#define FC 								M20//计算公式在文件说明内

#define BASE_FREQ 						34700000//34.7M基频
#define BASE_FREQ_SHIFT_LIMIT 			5000//5000偏移范围

/* 私有（静态）函数声明 ------------------------------------------------------*/ 
static void AD9851_Write(uint8_t*Control_Word);

/* 全局变量定义 --------------------------------------------------------------*/ 
 
/* 全局函数编写 --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : AD9851_Init()     
* @Description   : AD9851初始化程序 
* @Data          : 2016/7/20
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void AD9851_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
								  |GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOG, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12|GPIO_Pin_10|GPIO_Pin_11 ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//AD9851 初始化	
	AD9851_WCLK=0;
	AD9851_FQUD=0;
	AD9851_RESET=1; 	// 高电平复位
	OSdelay_ms(100);		
	AD9851_RESET=0;
	OSdelay_ms(100);		 
}
 
  
/**----------------------------------------------------------------------------
* @FunctionName  : AD9851_Set()     
* @Description   : 设置AD9851的输出频率和相位
* @Data          : 2016/7/20
* @Explain        
-------------------------------------------------------------------------------
F:频率 分辨率为0.04Hz,最大频率Fmax=AD9851_SystemCloc/2.5
Phase:相位 1个单位表示Pi/16 即11.25度
------------------------------------------------------------------------------*/
void AD9851_Set(double F,uint8_t Phase)
{	
	uint32_t Freq;									 
	uint8_t CW[5];
	if(MULT)Freq=FC*F/6;
	else Freq=FC*F;
	
	CW[4] = Freq & 0xff;	    // 频率控制字最低字节LSB
	CW[3] = (Freq>>8) & 0xff;
	CW[2] = (Freq>>16) & 0xff;
	CW[1] = (Freq>>24) & 0xff;  // 频率控制字最高字节MSB
	CW[0] = (Phase<<3)|(POWER_MODE<<2)|MULT; 
	AD9851_Write(CW);
}
 
 
/**----------------------------------------------------------------------------
* @FunctionName  : AD9851_FM()     
* @Description   : 发送FM
* @Data          : 2016/7/24
* @Explain        
-------------------------------------------------------------------------------
Vol:幅值 0~3.3V
------------------------------------------------------------------------------*/
void AD9851_FM(double Vol)
{	
	u32 TempVol = Vol*10000/3.3f;//转换成Hz
	if(TempVol > BASE_FREQ_SHIFT_LIMIT*2) TempVol = BASE_FREQ_SHIFT_LIMIT*2; 
	AD9851_Set((BASE_FREQ - BASE_FREQ_SHIFT_LIMIT)+TempVol,0);
}
  

/**----------------------------------------------------------------------------
* @FunctionName  : AD9851_Set()     
* @Description   : 写AD9851控制字，并行模式
* @Data          : 2016/7/20
* @Explain        
-------------------------------------------------------------------------------
Control_Word:控制字指针
------------------------------------------------------------------------------*/  
static void AD9851_Write(uint8_t*Control_Word)
{
	AD9851_FQUD=0;			   // FQ_UD置低
	AD9851_WCLK=0;			   // w_clk置低
	/*---并行传输控制字---*/
		AD9851_Data = Control_Word[0];
		AD9851_WCLK = 1;		
		AD9851_WCLK = 0;	 
		AD9851_Data = Control_Word[1];
		AD9851_WCLK = 1;		
		AD9851_WCLK = 0;
		AD9851_Data = Control_Word[2];
		AD9851_WCLK = 1;	
		AD9851_WCLK = 0;	
		AD9851_Data = Control_Word[3];
		AD9851_WCLK = 1;	
		AD9851_WCLK = 0;
		AD9851_Data = Control_Word[4];
		AD9851_WCLK = 1;	
		AD9851_WCLK = 0;		
		AD9851_FQUD = 1;  //上升沿更新频率
		AD9851_FQUD = 0;
} 
 
 

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





