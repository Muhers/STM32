#include "Light_Transfer.h"
	



	
void Light_Transfer_Main(void)
{
	
		static u32 bit=0,i=0,Flag=0; 
		if(Flag){Flag=0;Light_Singel=0;}
		if(Adjust_Flag==1) { Flag=1;bit=1;Singel_Flag=1;Adjust_Flag=0;return;}//周期时间校对 
		
		if(bit==0){bit=1;return;}
		if(bit<=8&&bit>=1)//数据位 1~8
		{
			
			Singel_Flag=0;//正在传输 
			if(Light_Singel<3) {return;}//防止杂波干扰
			
			if(Light_Singel<12);
			else if(Light_Singel<20) {i=1;while(i--) Light_Data[bit++]=0;}
			else if(Light_Singel<28) {i=2;while(i--) Light_Data[bit++]=0;}
			else if(Light_Singel<36) {i=3;while(i--) Light_Data[bit++]=0;}
			else if(Light_Singel<44) {i=4;while(i--) Light_Data[bit++]=0;}
			else if(Light_Singel<52) {i=5;while(i--) Light_Data[bit++]=0;}
			else if(Light_Singel<60) {i=6;while(i--) Light_Data[bit++]=0;}
			else if(Light_Singel<68) {i=7;while(i--) Light_Data[bit++]=0;}
			else if(Light_Singel<76) {i=8;while(i--) Light_Data[bit++]=0;}
			
			Light_Data[bit++]=1; 
			
		}
		if(bit==99) bit=0;
		if(bit>=9)
		{
		bit=99;
		Singel_Flag=1;//传输完毕
		}
		
	
}


	

	




	
	




	
	





