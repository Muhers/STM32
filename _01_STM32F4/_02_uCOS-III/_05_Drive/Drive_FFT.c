#include "Drive_FFT.h"
 
struct compx {float real,imag;};                             		//定义一个复数结构
struct compx s[FFT_N];    		//FFT输入和输出：从S[0]开始存放，根据大小自己定义
float SIN_TAB[FFT_N/4+1];   	//定义正弦表的存放空间



struct compx EE(struct compx a,struct compx b)      
{
 struct compx c;
 c.real=a.real*b.real-a.imag*b.imag;
 c.imag=a.real*b.imag+a.imag*b.real;
 return(c);
}

                     
	
void FFT_Get_dat(void)//得到原始数据
{

	u32 i; 
	for(i=0;i<FFT_N;i++)
	{                                  
		s[i].real= ADC1_Buff[i]*3.3/4096.0f;
	} 
	
	
}



void create_sin_tab(float *sin_t)                     
{
  unsigned int i;
  for(i=0;i<=FFT_N/4;i++)
  sin_t[i]=sin(2*PI*i/FFT_N);
}



float sin_tab(float pi)
{
  int n;
  float a;
   n=(u16)(pi*FFT_N/2/PI);
   
  if(n>=0&&n<=FFT_N/4)
    a=SIN_TAB[n];
  else if(n>FFT_N/4&&n<FFT_N/2)
    {
     n-=FFT_N/4;
     a=SIN_TAB[FFT_N/4-n];
    }
  else if(n>=FFT_N/2&&n<3*FFT_N/4)
    {
     n-=FFT_N/2;
     a=-SIN_TAB[n];
   }
  else if(n>=3*FFT_N/4&&n<3*FFT_N)
    {
     n=FFT_N-n;
     a=-SIN_TAB[n];
   }
  
  return a;
}



float cos_tab(float pi)
{
   float a,pi2;
   pi2=pi+PI/2;
   if(pi2>2*PI)
     pi2-=2*PI;
   a=sin_tab(pi2);
   return a;
}


void FFT(struct compx *xin)
{
  int f,m,nv2,nm1,i,k,l,j=0;
  struct compx u,w,t;
   
   nv2=FFT_N/2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
   nm1=FFT_N-1;  
   for(i=0;i<nm1;i++)        
   {
    if(i<j)                    //如果i<j,即进行变址
     {
      t=xin[j];           
      xin[j]=xin[i];
      xin[i]=t;
     }
    k=nv2;                    //求j的下一个倒位序
    while(k<=j)               //如果k<=j,表示j的最高位为1   
     {           
      j=j-k;                 //把最高位变成0
      k=k/2;                 //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
     }
   j=j+k;                   //把0改为1
  }

  {
   int le,lei,ip;                            //FFT运算核，使用蝶形运算完成FFT运算
    f=FFT_N;
   for(l=1;(f=f/2)!=1;l++)                  //计算l的值，即计算蝶形级数
           ;
  for(m=1;m<=l;m++)                         // 控制蝶形结级数
   {                                        //m表示第m级蝶形，l为蝶形级总数l=log（2）N
    le=2<<(m-1);                            //le蝶形结距离，即第m级蝶形的蝶形结相距le点
    lei=le/2;                               //同一蝶形结中参加运算的两点的距离
    u.real=1.0;                             //u为蝶形结运算系数，初始值为1
    u.imag=0.0;
    //w.real=cos(PI/lei);                  //不适用查表法计算sin值和cos值
    // w.imag=-sin(PI/lei);
    w.real=cos_tab(PI/lei);                //w为系数商，即当前系数与前一个系数的商
    w.imag=-sin_tab(PI/lei);
    for(j=0;j<=lei-1;j++)                  //控制计算不同种蝶形结，即计算系数不同的蝶形结
     {
      for(i=j;i<=FFT_N-1;i=i+le)           //控制同一蝶形结运算，即计算系数相同蝶形结
       {
        ip=i+lei;                          //i，ip分别表示参加蝶形运算的两个节点
        t=EE(xin[ip],u);                   //蝶形运算，详见公式
        xin[ip].real=xin[i].real-t.real;
        xin[ip].imag=xin[i].imag-t.imag;
        xin[i].real=xin[i].real+t.real;
        xin[i].imag=xin[i].imag+t.imag;
        
       }
      u=EE(u,w);                          //改变系数，进行下一个蝶形运算
     }
   }
  }
  
}
  
void FFT_Exchange(u16 *Buff)   
{  
  unsigned int i;  
  
  create_sin_tab(SIN_TAB);
  for(i=0;i<FFT_N;i++)                           //给结构体赋值
  {
	  s[i].real=10+5*sin((6.28318*i-1)/FFT_N); //实部为正弦波FFT_N点采样，赋值为1
     if(i<8)
	  s[i].real=10+5*sin((50*3.14159*i)/FFT_N); //实部为正弦波FFT_N点采样，赋值为1
     else if(i<24)
	  s[i].real=0;
	 else 
      s[i].real=10;
	 s[i].imag=0;                                //虚部为0
  }
	FFT_Get_dat();
	FFT(s);                                        //进行快速福利叶变换
  
  for(i=0;i<FFT_N;i++)                           //求变换后结果的模值，存入复数的实部部分
    Buff[i]=sqrt(s[i].real*s[i].real+s[i].imag*s[i].imag)/10;
	
 
}




















