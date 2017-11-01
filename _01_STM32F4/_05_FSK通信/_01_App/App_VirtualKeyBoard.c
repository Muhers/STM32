/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_VirtualKeyBoard.c
* @Description : None
* @Date        : 2016/8/22
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_VirtualKeyBoard.h"  
 
/* ˽�к궨�� ----------------------------------------------------------------*/
#define		KEY_BOARD_X			0
#define		KEY_BOARD_Y			240


/* ˽�У���̬���������� ------------------------------------------------------*/
static void VirtualKey_Show(u8 _ASCII_Key,u8 Mode);
static void VirtualKey_Code_Creat(void);  
Type_AppList App_VK_Scan;	

/* ȫ�ֱ������� --------------------------------------------------------------*/
const u8 ASCII_Key[36] =  	   {'0','1','2','3','4','5','6','7','8','9',
								'Q','W','E','R','T','Y','U','I','O','P',
								'A','S','D','F','G','H','J','K','L',
								'Z','X','C','V','B','N','M'};  
			 
Type_VKBoard VKBoard[256] = {0};					
u8 VKBoard_Aa = 0;//��Сд   0Сд,1 ��д��2������ 
u8 VKBoard_ResultCh[MESSAGE_LENTH] = {0};//���	
u8 VKBoard_Cnt = 0;	 

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : VirtualKeyBoard()     
* @Description   : None 
* @Data          : 2016/8/22
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int VirtualKeyBoard_Main(void)		
{    
	u16 i = 0;
	
	VirtualKey_FullShow(0); //��̬ˢ��
	
	for(i = 0;i < 36;i ++) //�����ַ�������
	{
		
		if(VKBoard[ASCII_Key[i]].LastState == 2)
		{ 
			VKBoard[ASCII_Key[i]].LastState = 0;
		 
			if(VKBoard_Aa == 0) //Сдģʽ
			{
				if(ASCII_Key[i] > '9')
				VKBoard_ResultCh[VKBoard_Cnt] = ASCII_Key[i] + 32;
				else  
				VKBoard_ResultCh[VKBoard_Cnt] = ASCII_Key[i]; 
			
				VKBoard_ResultCh[VKBoard_Cnt + 1] = 0;//��ֹͣλ
				
				VKBoard_Cnt ++;			
				if(VKBoard_Cnt > MESSAGE_LENTH-1) VKBoard_Cnt = MESSAGE_LENTH-1;
			}
			
			else if(VKBoard_Aa == 1)//��д
			{ 
				VKBoard_ResultCh[VKBoard_Cnt] = ASCII_Key[i]; 
			
				VKBoard_ResultCh[VKBoard_Cnt + 1] = 0;//��ֹͣλ
				
				VKBoard_Cnt ++;			
				if(VKBoard_Cnt > MESSAGE_LENTH-1) VKBoard_Cnt = MESSAGE_LENTH-1;
			}
			
			else if(VKBoard_Aa == 2) //������ģʽ
			{
				if(VKBoard_ResultCh[VKBoard_Cnt] >= '0' && VKBoard_ResultCh[VKBoard_Cnt]<='9')
				{
					VKBoard_ResultCh[VKBoard_Cnt] = ASCII_Key[i];  
					VKBoard_ResultCh[VKBoard_Cnt + 1] = 0;//��ֹͣλ
					
					VKBoard_Cnt ++;			
					if(VKBoard_Cnt > MESSAGE_LENTH-1) VKBoard_Cnt = MESSAGE_LENTH-1;
				}
			}
			
			
		}
	}
	
	return 0;																	
}		
 			
unsigned int VirtualKeyBoard_Start(void)	
{ 
	OSTask_Creat(&App_Touch);
	OSTask_Creat(&App_VK_Scan);
	VirtualKey_Code_Creat(); 
	VirtualKey_FullShow(1); 
	return 0;
}	
Type_AppList App_VirtualKeyBoard = {VirtualKeyBoard_Main,NULL,VirtualKeyBoard_Start,NULL, \
								OS_STATE_ACTIVE,OS_THREAD_FREE, \
								(u8*)"App_VirtualKeyBoard",10};			
																
																
/**----------------------------------------------------------------------------
* @FunctionName  : VK_Scan()     
* @Description   : �������ɨ�� 
* @Data          : 2016/8/22
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int VK_Scan_Main(void)		
{    
	u16 i = 0; 
	
	for(i = 0;i < 36;i ++)
		if(Touch_Judge(VKBoard[ASCII_Key[i]].x1,VKBoard[ASCII_Key[i]].y1,VKBoard[ASCII_Key[i]].x2,VKBoard[ASCII_Key[i]].y2) == TOUCH_VALID) //�а�ť������
		{ 
			VKBoard[ASCII_Key[i]].State = 1;
			VKBoard[ASCII_Key[i]].LastState = 1;
		}
		else 
		{ 
			VKBoard[ASCII_Key[i]].State = 0;
			if(VKBoard[ASCII_Key[i]].LastState == 1) VKBoard[ASCII_Key[i]].LastState = 2;//���º�����
		}
	return 0;																	
}		
 	 
Type_AppList App_VK_Scan = {VK_Scan_Main,NULL,NULL,NULL, \
								OS_STATE_ACTIVE,OS_THREAD_SYSTEM, \
								(u8*)"App_VirtualKeyBoard",50};			
		
 
/**----------------------------------------------------------------------------
* @FunctionName  : VirtualKey_Show()     
* @Description   : ����������ʾ 
* @Data          : 2016/8/22
* @Explain       : Mode ��0ˢ����ʾ��1ǿ����ʾ
------------------------------------------------------------------------------*/								
static void VirtualKey_Show(u8 _ASCII_Key,u8 Mode)
{  
	static u8 LastState[256] = {0};
	
	if(VKBoard[_ASCII_Key].Used == 0) return;  
	
	if(Mode == 1)
	{
			
		if(VKBoard[_ASCII_Key].State == 0)
		{
			OS_Rect_Draw(VKBoard[_ASCII_Key].x1,VKBoard[_ASCII_Key].y1,VKBoard[_ASCII_Key].x2,VKBoard[_ASCII_Key].y2,0,VKBoard[_ASCII_Key].BackColor);  
			OS_Rect_Draw(VKBoard[_ASCII_Key].x1 + 1,VKBoard[_ASCII_Key].y1 + 1,VKBoard[_ASCII_Key].x2 - 1,VKBoard[_ASCII_Key].y2 - 1,0,VKBoard[_ASCII_Key].BackColor); 
		}
		else if(VKBoard[_ASCII_Key].State == 1)//������
		{
			OS_Rect_Draw(VKBoard[_ASCII_Key].x1,VKBoard[_ASCII_Key].y1,VKBoard[_ASCII_Key].x2,VKBoard[_ASCII_Key].y2,0,~VKBoard[_ASCII_Key].BackColor);  
			OS_Rect_Draw(VKBoard[_ASCII_Key].x1 + 1,VKBoard[_ASCII_Key].y1 + 1,VKBoard[_ASCII_Key].x2 - 1,VKBoard[_ASCII_Key].y2 - 1,0,~VKBoard[_ASCII_Key].BackColor); 
		} 
		
		TextColor = VKBoard[_ASCII_Key].TextColor;
		BackColor = BLACK; 
		if(VKBoard_Aa == 0)  
		{
			if(_ASCII_Key > '9')  
				OS_Char_Show(VKBoard[_ASCII_Key].x1 + (VKBoard[_ASCII_Key].x2 - VKBoard[_ASCII_Key].x1)/2 - 8,VKBoard[_ASCII_Key].y1 + (VKBoard[_ASCII_Key].y2 - VKBoard[_ASCII_Key].y1)/2 - 16,_ASCII_Key + 32,32,1);//Сд
			else 
				OS_Char_Show(VKBoard[_ASCII_Key].x1 + (VKBoard[_ASCII_Key].x2 - VKBoard[_ASCII_Key].x1)/2 - 8,VKBoard[_ASCII_Key].y1 + (VKBoard[_ASCII_Key].y2 - VKBoard[_ASCII_Key].y1)/2 - 16,_ASCII_Key,32,1);//����
		}
		else if(VKBoard_Aa == 1)
			OS_Char_Show(VKBoard[_ASCII_Key].x1 + (VKBoard[_ASCII_Key].x2 - VKBoard[_ASCII_Key].x1)/2 - 8,VKBoard[_ASCII_Key].y1 + (VKBoard[_ASCII_Key].y2 - VKBoard[_ASCII_Key].y1)/2 - 16,_ASCII_Key,32,1);//��д
		else if(VKBoard_Aa ==2)
		{
			if(_ASCII_Key >= '0' && _ASCII_Key <= '9')
			OS_Char_Show(VKBoard[_ASCII_Key].x1 + (VKBoard[_ASCII_Key].x2 - VKBoard[_ASCII_Key].x1)/2 - 8,VKBoard[_ASCII_Key].y1 + (VKBoard[_ASCII_Key].y2 - VKBoard[_ASCII_Key].y1)/2 - 16,_ASCII_Key,32,1);//����
		}
	}
	else
	{
		if(LastState[_ASCII_Key] != VKBoard[_ASCII_Key].State)
		{
			LastState[_ASCII_Key] = VKBoard[_ASCII_Key].State;
			if(VKBoard[_ASCII_Key].State == 0) 
			{
				OS_Rect_Draw(VKBoard[_ASCII_Key].x1,VKBoard[_ASCII_Key].y1,VKBoard[_ASCII_Key].x2,VKBoard[_ASCII_Key].y2,0,VKBoard[_ASCII_Key].BackColor);  
				OS_Rect_Draw(VKBoard[_ASCII_Key].x1 + 1,VKBoard[_ASCII_Key].y1 + 1,VKBoard[_ASCII_Key].x2 - 1,VKBoard[_ASCII_Key].y2 - 1,0,VKBoard[_ASCII_Key].BackColor); 
		  
			}
			else if(VKBoard[_ASCII_Key].State == 1)//������
			{
				OS_Rect_Draw(VKBoard[_ASCII_Key].x1,VKBoard[_ASCII_Key].y1,VKBoard[_ASCII_Key].x2,VKBoard[_ASCII_Key].y2,0,~VKBoard[_ASCII_Key].BackColor);  
				OS_Rect_Draw(VKBoard[_ASCII_Key].x1 + 1,VKBoard[_ASCII_Key].y1 + 1,VKBoard[_ASCII_Key].x2 - 1,VKBoard[_ASCII_Key].y2 - 1,0,~VKBoard[_ASCII_Key].BackColor); 
			
			}  
		}
		
	}
	
	
 
	
}

 
 
/**----------------------------------------------------------------------------
* @FunctionName  : VirtualKey_FullShow()     
* @Description   : ����ȫ����ʾ 
* @Data          : 2016/8/22
* @Explain       : Mode ��0ˢ����ʾ��1ǿ����ʾ
------------------------------------------------------------------------------*/								
void VirtualKey_FullShow(u8 Mode)
{ 
	u16 i = 0;  
	
	for(i = 0;i < 255; i++)
		VirtualKey_Show(i,Mode); 
}



/**----------------------------------------------------------------------------
* @FunctionName  : VirtualKey_Code_Creat()     
* @Description   : ������������
* @Data          : 2016/8/22
* @Explain       : None
------------------------------------------------------------------------------*/	
static void VirtualKey_Code_Creat(void)
{ 
	u8 Frame = 3;//�߿�
	u16 StartX = 0,StartY = 0,Width = 0,Hight = 0;
	u16 i = 0; 
	u8 ASCII_Num[10] = {'0','1','2','3','4','5','6','7','8','9'};
	u8 ASCII_Char1[10] = {'Q','W','E','R','T','Y','U','I','O','P'};
	u8 ASCII_Char2[10] = {'A','S','D','F','G','H','J','K','L'};
	u8 ASCII_Char3[10] = {'Z','X','C','V','B','N','M'};
	
	/* ��ɫ ---------------------------------------------*/
	for(i = 0;i < 255; i++)
	{
		VKBoard[i].BackColor = GREEN; 
		VKBoard[i].TextColor = WHITE;
	}
	
	/* ���� ---------------------------------------------*/
	StartX = 45;
	StartY = KEY_BOARD_Y;
	Width = 70;
	Hight = 60; 
	for(i = 0;i < 10;i ++)
	{
		VKBoard[ASCII_Num[i]].x1 = StartX + i*Width + Frame;	
		VKBoard[ASCII_Num[i]].y1 = StartY + Frame;	
		VKBoard[ASCII_Num[i]].x2 = StartX + (i + 1)*Width - Frame;	
		VKBoard[ASCII_Num[i]].y2 = StartY + Hight - Frame;	
		VKBoard[ASCII_Num[i]].Used = 1;
	}
	
	/* ��һ����ĸ ---------------------------------------*/
 	StartX += 50;
	StartY += 60;
	Width = 60;
	Hight = 60; 
	for(i = 0;i < 10;i ++)
	{
		VKBoard[ASCII_Char1[i]].x1 = StartX + i*Width + Frame;	
		VKBoard[ASCII_Char1[i]].y1 = StartY + Frame;	
		VKBoard[ASCII_Char1[i]].x2 = StartX + (i + 1)*Width - Frame;	
		VKBoard[ASCII_Char1[i]].y2 = StartY + Hight - Frame;	
		VKBoard[ASCII_Char1[i]].Used = 1;
	}
	
	/* �ڶ�����ĸ ---------------------------------------*/
	StartX += 30;
	StartY += 60;
	Width = 60;
	Hight = 60; 
	for(i = 0;i < 9;i ++)
	{
		VKBoard[ASCII_Char2[i]].x1 = StartX + i*Width + Frame;	
		VKBoard[ASCII_Char2[i]].y1 = StartY + Frame;	
		VKBoard[ASCII_Char2[i]].x2 = StartX + (i + 1)*Width - Frame;	
		VKBoard[ASCII_Char2[i]].y2 = StartY + Hight - Frame;
		VKBoard[ASCII_Char2[i]].Used = 1;	
	}
	
	/* ��������ĸ ---------------------------------------*/
	StartX += 60;
	StartY += 60;
	Width = 60;
	Hight = 60; 
	for(i = 0;i < 7;i ++)
	{
		VKBoard[ASCII_Char3[i]].x1 = StartX + i*Width + Frame;	
		VKBoard[ASCII_Char3[i]].y1 = StartY + Frame;	
		VKBoard[ASCII_Char3[i]].x2 = StartX + (i + 1)*Width - Frame;	
		VKBoard[ASCII_Char3[i]].y2 = StartY + Hight - Frame;
		VKBoard[ASCII_Char3[i]].Used = 1;	
	}
 
		
}







void VK_Buff_Clear(void)
{
	u16 i = 0;
	for(i = 0;i < MESSAGE_LENTH;i++)
	{
		VKBoard_ResultCh[i] = 0;
	}
	VKBoard_Cnt = 0;
}



 
								
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





























