/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Key.c
* @Description : None
* @Date        : 2016/7/19
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Key.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/
 
/* 私有（静态）函数声明 ------------------------------------------------------*/ 
Type_AppList App_Key_Scan;

/* 全局变量定义 --------------------------------------------------------------*/
static Type_Key Key = {0};  
static void Key_GPIO_Init(void);

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Key()     
* @Description   : 按键程序 
* @Data          : 2016/7/19
* @Explain       : 按键状态机扫描
------------------------------------------------------------------------------*/
int Key_Main(void)		
{   
	u16 i = 0; 
	if(!KEY_PRESS) //没有按键按下
	{
		for(i = 0;i < KEY_NUM_MAX;i ++)
		{
			if(Key.CountLast[i] > KEY_MODE_SHORT && Key.CountLast[i] < KEY_COUNT_LONG)  
			Key.ResultShort |= (0x0001<<i);
			 
		} 
		
		for(i = 0;i < KEY_NUM_MAX;i ++)
			Key.CountLast[i] = 0;
	}		
	else {Key.ResultShort = 0; Key.ResultLong = 0;}
	
	return 0;																	
}	 						

int Key_Start(void)		
{			
	static u16 first = 0;
	if(first == 0)
	{
		first = 1;	
//		GPIO_Key_Init();
		Key_GPIO_Init();
		
		
		OSTask_Creat(&App_Key_Scan);  	  	
	}
	return 0;
}
Type_AppList App_Key = {Key_Main,NULL,Key_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_SYSTEM, \
						(u8*)"Key",100};

						
/**----------------------------------------------------------------------------
* @FunctionName  : KeyScan()     
* @Description   : None 
* @Data          : 2016/7/19
* @Explain       : None
------------------------------------------------------------------------------*/
int Key_Scan_Main(void)		
{       
	if( GPIO_UP		== 0)	{ Key.CountNow[0]++;Key.CountLast[0]++;}else Key.CountNow[0]= 0; 
	if( GPIO_DOWN	== 0)	{ Key.CountNow[1]++;Key.CountLast[1]++;}else Key.CountNow[1]= 0; 
	if( GPIO_LEFT	== 0)	{ Key.CountNow[2]++;Key.CountLast[2]++;}else Key.CountNow[2]= 0; 
	if( GPIO_RIGHT  == 0)   { Key.CountNow[3]++;Key.CountLast[3]++;}else Key.CountNow[3]= 0; 
	if( GPIO_LEARN  == 0)   { Key.CountNow[4]++;Key.CountLast[4]++;}else Key.CountNow[4]= 0; 
	if( GPIO_FUNC1  == 0)   { Key.CountNow[5]++;Key.CountLast[5]++;}else Key.CountNow[5]= 0; 
	if( GPIO_FUNC2  == 0)   { Key.CountNow[6]++;Key.CountLast[6]++;}else Key.CountNow[6]= 0; 
	if( GPIO_FSAVE  == 0)   { Key.CountNow[7]++;Key.CountLast[7]++;}else Key.CountNow[7]= 0; 
	if( GPIO_FREAD  == 0)   { Key.CountNow[8]++;Key.CountLast[8]++;}else Key.CountNow[8]= 0; 
	if( GPIO_FERASE == 0)   { Key.CountNow[9]++;Key.CountLast[9]++;}else Key.CountNow[9]= 0; 
	 
	return 0;																	
}	 
Type_AppList App_Key_Scan = {Key_Scan_Main,NULL,NULL,NULL, \
							OS_STATE_ACTIVE,OS_THREAD_SYSTEM, \
							(u8*)"Key_Scan",10};			
 
						
/**----------------------------------------------------------------------------
* @FunctionName  : Key_Now_Get()     
* @Description   : 按键现状获取函数 
* @Data          : 2016/7/19
* @Explain       
-------------------------------------------------------------------------------		
 @param  	KeyNum: WK_UP|KEY1|KEY2|KEY3	
			Mode: KEY_MODE_SHORT|KEY_MODE_LONG						
 @return 	0（无效）,1（有效）							
------------------------------------------------------------------------------*/ 
u16 Key_Now_Get(u16 KeyNum,u16 Mode)
{
	u16 Result = 0;  
	if(Mode & KEY_MODE_SHORT)
	{
		if(KeyNum&UP	)if(Key.CountNow[0] > KEY_MODE_SHORT) Result |= UP		;	 
		if(KeyNum&DOWN	)if(Key.CountNow[1] > KEY_MODE_SHORT) Result |= DOWN	; 
		if(KeyNum&LEFT	)if(Key.CountNow[2] > KEY_MODE_SHORT) Result |= LEFT	;
		if(KeyNum&RIGHT	)if(Key.CountNow[3] > KEY_MODE_SHORT) Result |= RIGHT	; 
		if(KeyNum&LEARN	)if(Key.CountNow[4] > KEY_MODE_SHORT) Result |= LEARN	; 
		if(KeyNum&FUNC1	)if(Key.CountNow[5] > KEY_MODE_SHORT) Result |= FUNC1	;
		if(KeyNum&FUNC2	)if(Key.CountNow[6] > KEY_MODE_SHORT) Result |= FUNC2	; 
		if(KeyNum&FSAVE	)if(Key.CountNow[7] > KEY_MODE_SHORT) Result |= FSAVE	; 
		if(KeyNum&FREAD	)if(Key.CountNow[8] > KEY_MODE_SHORT) Result |= FREAD	;
		if(KeyNum&FERASE)if(Key.CountNow[9] > KEY_MODE_SHORT) Result |= FERASE	;   
	}
	else if(Mode & KEY_MODE_LONG)
	{ 
		if(KeyNum&UP	)if(Key.CountNow[0] > KEY_COUNT_LONG) Result |= UP		;	 
		if(KeyNum&DOWN	)if(Key.CountNow[1] > KEY_COUNT_LONG) Result |= DOWN	; 
		if(KeyNum&LEFT	)if(Key.CountNow[2] > KEY_COUNT_LONG) Result |= LEFT	;	
		if(KeyNum&RIGHT	)if(Key.CountNow[3] > KEY_COUNT_LONG) Result |= RIGHT	; 
		if(KeyNum&LEARN	)if(Key.CountNow[4] > KEY_COUNT_LONG) Result |= LEARN	; 
		if(KeyNum&FUNC1	)if(Key.CountNow[5] > KEY_COUNT_LONG) Result |= FUNC1	;
		if(KeyNum&FUNC2	)if(Key.CountNow[6] > KEY_COUNT_LONG) Result |= FUNC2	; 
		if(KeyNum&FSAVE	)if(Key.CountNow[7] > KEY_COUNT_LONG) Result |= FSAVE	; 
		if(KeyNum&FREAD	)if(Key.CountNow[8] > KEY_COUNT_LONG) Result |= FREAD	;
		if(KeyNum&FERASE)if(Key.CountNow[9] > KEY_COUNT_LONG) Result |= FERASE	; 
	}
		
	if(Result == KeyNum) return 1;
	else return 0;  
}

/**----------------------------------------------------------------------------
* @FunctionName  : Key_Get()     
* @Description   : 按键获取函数 
* @Data          : 2016/7/19
* @Explain       ：可用 | 连接个参数
 -------------------------------------------------------------------------------		
 @param  	KeyNum: WK_UP|KEY1|KEY2|KEY3	
			Mode: KEY_MODE_SHORT|KEY_MODE_LONG
 @return 	0（无效）,1（有效）							
------------------------------------------------------------------------------*/ 
u16 Key_Get(u16 KeyNum,u16 Mode)
{ 
	if(Mode & KEY_MODE_SHORT)
	{ 
		if(Key.ResultShort == KeyNum) return 1;
		else return 0; 
	}
	if(Mode & KEY_MODE_LONG)
	{ 
		if(Key.ResultLong == KeyNum) return 1;
		else return 0; 
	}
	return 0;	
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : Key_Clear()     
* @Description   : 按键清除函数 
* @Data          : 2016/7/19
* @Explain       ：可用 | 连接个参数  
-------------------------------------------------------------------------------		
 与Key_Get()配套使用
 @param Mode: KEY_MODE_SHORT|KEY_MODE_LONG
------------------------------------------------------------------------------*/
void Key_Clear(u16 Mode)
{ 
	if(Mode & KEY_MODE_SHORT) Key.ResultShort = 0;
	if(Mode & KEY_MODE_LONG)  Key.ResultLong = 0;
}



static void Key_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOA,GPIOE时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_0|GPIO_Pin_6|GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉 
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE0,2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_14; 
	GPIO_Init(GPIOG, &GPIO_InitStructure);
}
	
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/


















