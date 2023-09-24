#include "exti.h"
#include "oled.h"
#include "comm.h"
#include "delay.h"

/**************************************************************************
函数功能：按键外部中断初始化 A6,A7
入口参数：无
返回  值：无 
**************************************************************************/
void Key_EXTI_Init(void)
{  
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	            //端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	            //端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
  	
		EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
}

/**************************************************************************
函数功能：光电门信号外部中断初始化 A0,1,2,3
入口参数：无
返回  值：无 
**************************************************************************/
void Gate_EXTI_Init(void)
{  
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	            //端口配置
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;         //浮空输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
  	
		EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		
/******************NVIC*******************/		

		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
}

/**************************************************************************
函数功能：外部中断Line4服务函数
入口参数：无
返回  值：无 
**************************************************************************/
void EXTI0_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line0)!=RESET)//验证EXIT LINE中断信号
     {
        
				
        EXTI_ClearITPendingBit(EXTI_Line0); //清除EXIT LINE中断标志位
     }
}

void EXTI1_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line1)!=RESET)//验证EXIT LINE中断信号
     {
       	delay_ms(1);				 
        if(Key1==1)
				{
					EMR=1;
					if(statu==4)
						statu=3;
				}
				else if(Key1==0)
				{
					EMR=0;
					//statu=3;
				}
        EXTI_ClearITPendingBit(EXTI_Line1);  //清除EXIT LINE中断标志位
     }
}

void EXTI2_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line2)!=RESET)//验证EXIT LINE中断信号
     {
       
			 delay_ms(1);				 
        if(Key2==1) 
				{
					statu=1;
				}	
				else if(Key2==0)
				{
					if(statu!=3)
						statu=2;
				}
        EXTI_ClearITPendingBit(EXTI_Line2);  //清除EXIT LINE中断标志位
     }
}

void EXTI3_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line3)!=RESET)//验证EXIT LINE中断信号
     {
       
         	 
        EXTI_ClearITPendingBit(EXTI_Line3);  //清除EXIT LINE中断标志位
     }
}

