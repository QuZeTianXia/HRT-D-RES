#include "timer.h"
#include "adc.h"
#include "digitron.h"
#include "led.h"
#include "usart.h"
#include "as32.h"
#include "comm.h"

uint8_t count_ms=0;
uint8_t sec=0,min=0,hr=0;				//���ͼ�ʱ��
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
�������ܣ���ʱ��3��ʱ�жϳ�ʼ��
��ڲ�������ڲ�����arr���Զ���װֵ  psc��ʱ��Ԥ��Ƶ�� 
����  ֵ����
**************************************************************************/
void TIM3_IT_Init(u16 arr,u16 psc)	
{	 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ��TIM3ʱ��
		
	//��ʼ����ʱ��3 TIM3 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//��������ж�
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	
  TIM_Cmd(TIM3,ENABLE); 	//ʹ�ܶ�ʱ��3
}

/**************************************************************************
�������ܣ���ʱ��2�жϷ�����
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void TIM3_IRQHandler(void)
{ 	
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)//�жϱ�����	
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
						if(off_line>=101)          //�ȴ�200ms
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
									off_line=81;            //���ߺ�ÿ��300ms����һ��ֹͣ�ź�
									wireless_sta=0;
									Link_LED=0;
									statu=1;
								}
							}
						}
					}
					
					if(off_line==1 || off_line==11 ||off_line==21||off_line==31||off_line==41||off_line==51||off_line==61||off_line==71||off_line==81) //ÿ��0.2s����һ��״̬������7��
					{
						switch (statu)
						{
							case 1:
								as32=0xa0;
								AS32_Send(0x7a4b,as32);//�����ƶ�
								Stop_LED=(1&&flash);
								Ready_LED=0;
								Run_LED=0;
								break;
							case 2:
								as32=0xb0;
								AS32_Send(0x7a4b,as32);//׼��
								Stop_LED=0;
								Ready_LED=(1&&flash);
								Run_LED=0;
								break;
							case 3:
								as32=0xc0;
								AS32_Send(0x7a4b,as32);//��ͣ
								Stop_LED=(1&&flash);
								Ready_LED=(1&&flash);
								Run_LED=0;
								break;
							case 4:
								as32=0xd0;
								AS32_Send(0x7a4b,as32);//����
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
				TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//����жϱ�־λ 						
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
