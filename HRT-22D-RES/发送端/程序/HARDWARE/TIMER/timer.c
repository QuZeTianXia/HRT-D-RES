#include "timer.h"
#include "adc.h"
#include "digitron.h"
#include "led.h"
#include "usart.h"
#include "as32.h"
#include "comm.h"

uint8_t count_ms=0;
uint8_t sec=0,min=0,hr=0;				//发送计时器
uint8_t EMR=0;
uint8_t off_flag=0;
uint8_t car_statu=0;
uint8_t drop_count=0;
uint8_t Enable_value=0;
uint8_t ecu_statu=0;
uint8_t Voltage_limit[3]={66,75,80};
uint8_t as32=0;
uint8_t flash=1;

/**************************************************************************
函数功能：定时器3定时中断初始化
入口参数：入口参数：arr：自动重装值  psc：时钟预分频数 
返回  值：无
**************************************************************************/
void TIM3_IT_Init(u16 arr,u16 psc)	
{	 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIM3时钟
		
	//初始化定时器3 TIM3 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//允许更新中断
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	
  TIM_Cmd(TIM3,ENABLE); 	//使能定时器3
}

/**************************************************************************
函数功能：定时器2中断服务函数
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
void TIM3_IRQHandler(void)
{ 	
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)//中断被触发	
		{
					count_ms++;
					off_line++;
			
					if(EMR&&EMR<=100)
						EMR++;
					if(EMR>100&&(statu==2||statu==3))
						statu=4;
					
					if((count_ms%10)==0)
						ADCdeal();
					
					if(Dis_V>Voltage_limit[2])
					{
						POWER4=1;
						POWER3=1;
						POWER2=1;
						POWER1=1;
						flash =1;
					}
					else if(Dis_V>Voltage_limit[1])
					{
						POWER4=0;
						POWER3=1;
						POWER2=1;
						POWER1=1;
						flash =1;
					}
					else if(Dis_V>Voltage_limit[0])
					{
					  POWER4=0;
						POWER3=0;
						POWER2=1;
						POWER1=1;
						flash =1;
					}
					else 
          {						
						if(count_ms<100)
						{
					   POWER4=0;
						 POWER3=0;
						 POWER2=0;
						 POWER1=1;
						 flash =1;
						}
						else
						{
						 POWER4=0;
						 POWER3=0;
						 POWER2=0;
						 POWER1=0;			
             flash =0;							
						}
						
					}

					
					if(off_line>81)
					{
						if(off_line>=101)          //等待200ms
						{
							
							if(wireless_sta==1)
							{
								drop_count=0;
								off_line=1;
								wireless_sta=0;
								Link_LED=(1&&flash);
							}
							else
							{
								if(drop_count<2)
								{
									drop_count++;
									off_line=91;
								}
								else
								{
									off_line=81;            //掉线后每隔300ms发送一次停止信号
									wireless_sta=0;
									Link_LED=0;
									statu=1;
								}
							}
						}
					}
					
					if(off_line==1 || off_line==11 ||off_line==21||off_line==31||off_line==41||off_line==51||off_line==61||off_line==71||off_line==81) //每隔0.2s发送一次状态，共发7次
					{
						switch (statu)
						{
							case 1:
								as32=0xa0;
								AS32_Send(0x7a4b,as32);//紧急制动
								Stop_LED=(1&&flash);
								Ready_LED=0;
								Run_LED=0;
								break;
							case 2:
								as32=0xb0;
								AS32_Send(0x7a4b,as32);//准备
								Stop_LED=0;
								Ready_LED=(1&&flash);
								Run_LED=0;
								break;
							case 3:
								as32=0xc0;
								AS32_Send(0x7a4b,as32);//缓停
								Stop_LED=(1&&flash);
								Ready_LED=(1&&flash);
								Run_LED=0;
								break;
							case 4:
								as32=0xd0;
								AS32_Send(0x7a4b,as32);//运行
								Stop_LED=0;
								Ready_LED=0;
								Run_LED=(1&&flash);
								break;
							default:
								as32=0xa0;
								AS32_Send(0x7a4b,as32);
								Stop_LED=(1&&flash);
								Ready_LED=0;
								Run_LED=0;
								break;
						}
					}
				
				Timing();
				TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除中断标志位 						
	}
			      
}

void Timing(void)
{
	if(count_ms==100||count_ms>=200)
	{
		sec++;
		if(count_ms>=200)
			count_ms=0;		
	}
	
	if(sec>=60)
		sec=0, 
		min++;
	
	if(min>=60)
		min=0,
		hr++;		
}
