/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_DataSave.c
* @Description : None
* @Date        : 2016/11/23
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 数据存储
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_DataSave.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define SAVE_LENTH	 		400		//400*4 = 1.6k Byte
#define SAVE_ADDRESS		ADDR_FLASH_SECTOR_11   //存储位置

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : DataSave_Write()
* @Description   : None
* @Data          : 2016/11/23
* @Explain       : None
------------------------------------------------------------------------------*/
void DataSave_Write(void)
{
    u32 Temp_u32[SAVE_LENTH] = {0};
    Union_32 Union32 = {0};
    u16 i = 0,j = 0;
    u16 Save_Cnt = 0;

    //存入
    for(i = 0; i < LOAD_MAX; i++)
    {  
		Union32._u16[0] = Recognize_Source[i].Save_State; 
		Temp_u32[Save_Cnt++] = Union32._u32;  
		
		for(j = 0; j < WORK_STATE; j++)
		{ 
			Union32._float = Recognize_Source[i].Py[j]; 
			Temp_u32[Save_Cnt++] = Union32._u32; 
			
			Union32._float = Recognize_Source[i].Phase[j]; 
			Temp_u32[Save_Cnt++] = Union32._u32;  
		}  
    } 
	
    if(Save_Cnt >= SAVE_LENTH - 1)
    { 
		OLED_Str_Show(0,0,"[SaveData is too much!!!]",1);
        while(1);
    } 
	
    InFLASH_Write(SAVE_ADDRESS, Temp_u32, SAVE_LENTH);
}


/**----------------------------------------------------------------------------
* @FunctionName  : DataSave_Read()
* @Description   : None
* @Data          : 2016/11/23
* @Explain       : None
------------------------------------------------------------------------------*/
void DataSave_Read(void)
{
    u32 Temp_u32[SAVE_LENTH] = {0};
    Union_32 Union32 = {0};
    u16 i = 0,j=0;
    u16 Save_Cnt = 0;
	
    InFLASH_Read(SAVE_ADDRESS, Temp_u32, SAVE_LENTH); 
		
    //转存
    for(i = 0; i < LOAD_MAX; i++)
    {  
		Union32._u32 = Temp_u32[Save_Cnt++];   
		Recognize_Source[i].Save_State = Union32._u16[0];
		
		for(j = 0; j < WORK_STATE; j++)
		{ 
			Union32._u32 = Temp_u32[Save_Cnt++];   
			Recognize_Source[i].Py[j] = Union32._float;
			
			Union32._u32 = Temp_u32[Save_Cnt++];   
			Recognize_Source[i].Phase[j] = Union32._float;
		}
		  
    } 
	
	if(Save_Cnt >= SAVE_LENTH - 1)
    { 
		OLED_Str_Show(0,0,"[SaveData is too much!!!]",1);
        while(1);
    } 
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : DataSave_Erase()
* @Description   : None
* @Data          : 2016/11/23
* @Explain       : None
------------------------------------------------------------------------------*/
void DataSave_Erase(void)
{
	u32 Temp_u32[SAVE_LENTH] = {0};
	
	
	InFLASH_Write(SAVE_ADDRESS, Temp_u32, SAVE_LENTH);
}


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





