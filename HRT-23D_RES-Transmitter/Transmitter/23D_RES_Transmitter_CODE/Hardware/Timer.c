#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"


int Timenum = 0;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	
		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;	 //����һ���ṹ�������������ʼ����ʱ��
    NVIC_InitTypeDef NVIC_InitStructure;

	/* ������ʱ��2ʱ�� */
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//���TIMx���жϴ�����λ:TIM �ж�Դ
	TIM_TimeBaseInitStructure.TIM_Period =999;//�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71;//����������ΪTIMxʱ��Ƶ��Ԥ��Ƶֵ��100hz����Ƶ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);	
	
	/* �����жϲ����������ж� */
	
	
	/* ����NVIC���� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;  //��Ӧ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ��
	NVIC_Init(&NVIC_InitStructure);	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );	//ʹ�ܻ���ʧ��ָ����TIM�ж�
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܻ���ʧ��TIMx����
}


void TIM2_IRQHandler()      //��ʱ��2�жϺ���0.01s
{
	Timenum++;	
	if(Timenum>=100)			//����10Hz��pwm���ü���
	Timenum=0;
	


	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}	



