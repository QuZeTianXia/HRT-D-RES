#include "buzzer.h"

uint8_t beep_count=0;

void Bell_Init(void)  	//初始化
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	/********************端口初始化*********************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	          //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	
	/********************定时器4初始化*********************/
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能TIM4时钟
		
	//初始化定时器4 TIM4 
	TIM_TimeBaseStructure.TIM_Period = 999; //设定计数器自动重装值   100ms
	TIM_TimeBaseStructure.TIM_Prescaler =7199; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//允许更新中断
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级3级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
}


void Beep_100MS(uint8_t hd_ms)
{
	beep_count=hd_ms;
	Bell=1;
	TIM_Cmd(TIM4,ENABLE );
}

void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)//中断被触发	
				{
					if(beep_count)
						beep_count--;
					else 
					{
						Bell=0;
						TIM_Cmd(TIM4,DISABLE );
						beep_count=0;
					}
															
		   }
			 TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//清除中断标志位 	     
}
