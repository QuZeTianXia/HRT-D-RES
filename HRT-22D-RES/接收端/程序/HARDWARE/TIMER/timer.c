#include "timer.h"
#include "led.h"
#include "usart.h"
#include "E22.h"
#include "comm.h"
#include "can.h"

uint8_t count_ms=0;
uint8_t time_out=0;
uint8_t answer=0;
uint8_t stop_flag=0;
uint8_t can_rec=0;
uint8_t sec=0,min=0,hr=0;
uint8_t Rec_count=0;
uint8_t wireless_sta=0;			//0:ͨѶ�Ͽ� 1:ͨѶ����
uint8_t can_count=0;
uint8_t stop_count=0;
uint8_t send_count=0;
uint8_t buf[8];
extern uint8_t ECU_conneted;

/************************************************************************************************************************************
                                                       ��ʱ��3��ʱ�жϳ�ʼ��				
************************************************************************************************************************************/
			
			
			void TIM3_IT_Init(u16 arr,u16 psc)	
			{	 				
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				NVIC_InitTypeDef NVIC_InitStructure;

				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	      //ʹ��TIM3ʱ��
					
				//��ʼ����ʱ��3 TIM3 
				TIM_TimeBaseStructure.TIM_Period = arr;                     //�趨�������Զ���װֵ 
				TIM_TimeBaseStructure.TIM_Prescaler =psc; 	                //Ԥ��Ƶ��   
				TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //����ʱ�ӷָ�:TDTS = Tck_tim
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
				TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
				TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                    //��������ж�
				
				//�жϷ����ʼ��
				NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;             //TIM3�ж�
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�1��
				NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  				//�����ȼ�0��
				NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 						//IRQͨ����ʹ��
				NVIC_Init(&NVIC_InitStructure); 														//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
			
				TIM_Cmd(TIM3, ENABLE); 	                                    //ʹ�ܶ�ʱ��3			
			}

			
/************************************************************************************************************************************
                                                       ��ʱ��2�жϷ�����				
************************************************************************************************************************************/
			

void TIM3_IRQHandler(void)                                    //��ʱ���жϷ�����
{ 		    		  			    
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)              //�жϱ�����	
	{
		uint8_t CAN_msg[8];
		uint8_t E22;
		
		count_ms++;
		time_out++;
		can_count++;
		
		if(timer>0)
			timer--;
			
					
/************************************************************************************************************************************
                                                           CANͨѶ				
************************************************************************************************************************************/					


				if((count_ms%9)==0)
				{
					switch (statu)
					{
						case 1:
							CAN_msg[0]=0x00;   //�ƶ� 00000000
							break;
						
						case 2:
							CAN_msg[0]=0xa8;   //׼�� 10101000
							break;
						
						case 3:
							CAN_msg[0]=0xf8;   //��ͣ 11111000
							break;
						
						case 4:
							CAN_msg[0]=0xd0;   //���� 11010000
							break;
						
						default:
							CAN_msg[0]=0x00;
						break;
					}
							
					
					if(ECU_conneted)
						can_count=0;
					
					if(can_count>40)
						{
							if(stop_flag==1)
							  {CAN_msg[0]=CAN_msg[0]+0x03;}	   //����ˡ�ECUͬʱ����
						  else
					      {CAN_msg[0]=CAN_msg[0]+0x01;}    //ECU����
				    }
						
					else if(stop_flag==1)
						     CAN_msg[0]=CAN_msg[0]+0x02;     //����˶���
					
					Can_Send_Msg(0x117,CAN_msg,1);
					
				}
						

/************************************************************************************************************************************
					                                                ����ͨѶ����				
************************************************************************************************************************************/					
					
					
				if(ACK==1&&answer==1&&timer==0&&stop_flag==0)               //����ͽ����󣬼�ʱ160ms
						{                                                       //ʱ��֮�ڽ��յ�����ָ�״̬���Σ���60ms
							switch (statu)
							{
								case 1:
									E22=0xab;   //�ƶ�
									break;
								
								case 2:
									E22=0xcc;   //׼��
									break;
								
								case 3:
									E22=0x66;   //��ͣ
									break;
								
								case 4:
									E22=0x3f;   //����
									break;
								
								default:
									E22=0xab;
								break;
							}
							
							E22_Send(0x4e7a,E22);		                              //���ͳ���״̬	
								
							if(send_count>=3)		
								{						
									answer=1;
									wireless_sta=1;
									Rec_count=Rec_count+1;
								}
							
							time_out=0;	
							send_count++;
							
							if(send_count<4)
								timer=5;
							
							if(send_count>=4)
								send_count=0;
				
						}
							

/************************************************************************************************************************************
					                                                 ��ʱ�Ͽ�				
************************************************************************************************************************************/

				
				if(time_out>=100)                                 //��ʱ1���Ͽ�
					{
						statu=1;
						wireless_sta=0;
						stop_flag=1;						
					}

					
				if(stop_flag)                                       
					{
						stop_count++;
					}
			
				if(stop_count>150)                                         //����ͣ����1.5s�����ֹͣ����
					{
						stop_flag=0;
						time_out=0;
						stop_count=0;
					}		

					
					
/************************************************************************************************************************************
                                                        LED�źŵ�ָʾ				
************************************************************************************************************************************/					

				
				if(wireless_sta)                                           //���յ�����ͨѶ
					{
						if(Rec_count>=1)   
							{
								SysCom=0;                                          //LED2��
								Rec_count=0;
								answer=1;
								ACK=0;
							}  		
					}
				
				if(wireless_sta==0)                                        //δ���յ�����ͨѶ��LED2��
						SysCom=1;
				
			if(count_ms==50||count_ms==100)                            //LED1��˸��ָʾ������������
					  SysSta=~SysSta; 

				
				Timing();
					
				TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                 //����жϱ�־λ 						
	}
			      
}

/************************************************************************************************************************************
					                                                   ��ʱ��				
************************************************************************************************************************************/

			void Timing(void)
			{
				if(count_ms>=100)
					count_ms=0;
					sec++;
				
				if(sec>=60)
					sec=0,
					min++;
				
				if(min>=60)
					min=0,
					hr++;		
			}



