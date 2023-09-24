#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"


int Timenum = 0;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	
		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;	 //声明一个结构体变量，用来初始化定时器
    NVIC_InitTypeDef NVIC_InitStructure;

	/* 开启定时器2时钟 */
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除TIMx的中断待处理位:TIM 中断源
	TIM_TimeBaseInitStructure.TIM_Period =999;//设置自动重装载寄存器周期的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71;//设置用来作为TIMx时钟频率预分频值，100hz计数频率
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);	
	
	/* 设置中断参数，并打开中断 */
	
	
	/* 设置NVIC参数 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;  //响应优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//使能
	NVIC_Init(&NVIC_InitStructure);	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );	//使能或者失能指定的TIM中断
	TIM_Cmd(TIM2,ENABLE); //使能或者失能TIMx外设
}


void TIM2_IRQHandler()      //定时器2中断函数0.01s
{
	Timenum++;	
	if(Timenum>=100)			//配置10Hz的pwm配置计数
	Timenum=0;
	


	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}	



