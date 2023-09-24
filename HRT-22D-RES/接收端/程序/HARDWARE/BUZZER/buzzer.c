#include "buzzer.h"

uint8_t beep_count=0;

void Bell_Init(void)  	//��ʼ��
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	/********************�˿ڳ�ʼ��*********************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ�ܶ˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	          //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA 
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	
	/********************��ʱ��4��ʼ��*********************/
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM4ʱ��
		
	//��ʼ����ʱ��4 TIM4 
	TIM_TimeBaseStructure.TIM_Period = 999; //�趨�������Զ���װֵ   100ms
	TIM_TimeBaseStructure.TIM_Prescaler =7199; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//��������ж�
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
}


void Beep_100MS(uint8_t hd_ms)
{
	beep_count=hd_ms;
	Bell=1;
	TIM_Cmd(TIM4,ENABLE );
}

void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)//�жϱ�����	
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
			 TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//����жϱ�־λ 	     
}
