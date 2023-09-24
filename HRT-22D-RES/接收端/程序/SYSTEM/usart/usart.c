#include "sys.h"
#include "usart.h"	  
#include "motor.h"
#include "comm.h"
#include "timer.h"

uint8_t ACK=0;
uint8_t timer=0;

#if EN_USART1_RX   	  
			
			u8 USART_RX_BUF[USART_REC_LEN];
			u16 USART_RX_STA=0;   
			

/************************************************************************************************************************************
                                                     ��ʼ������GPIO�˿�					
************************************************************************************************************************************/

		void uart_init(u32 bound)
		{
			//GPIO�˿�����
			GPIO_InitTypeDef  GPIO_InitStructure;
			USART_InitTypeDef USART_InitStructure;
			NVIC_InitTypeDef  NVIC_InitStructure;
			 
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);     //ʹ��USART1��GPIOAʱ��
			
			//USART1_TX   GPIOA.9
			GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_9;                                    //PA.9
			GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_AF_PP;	                              //�����������
			GPIO_Init(GPIOA, &GPIO_InitStructure);                                          //��ʼ��GPIOA.9
			 
			//USART1_RX	  GPIOA.10��ʼ��
			GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_10;                                   //PA10
			GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IN_FLOATING;                         //��������
			GPIO_Init(GPIOA, &GPIO_InitStructure);                                      		//��ʼ��GPIOA.10  

			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                   		//��ռ���ȼ�2
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		                      		//�����ȼ�1
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			                        		//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure);	                                            		//����ָ���Ĳ�����ʼ��VIC�Ĵ���
			
			//USART ��ʼ������
			USART_InitStructure.USART_BaudRate   =  bound;                                  //���ڲ�����
			USART_InitStructure.USART_WordLength = 	USART_WordLength_8b;                    //�ֳ�Ϊ8λ���ݸ�ʽ
			USART_InitStructure.USART_StopBits   = 	USART_StopBits_1;                       //һ��ֹͣλ
			USART_InitStructure.USART_Parity     = 	USART_Parity_No;                        //����żУ��λ
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������������
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                //�շ�ģʽ

			USART_Init(USART1, &USART_InitStructure);																				//��ʼ������1
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);																	//�������ڽ����ж�
			USART_Cmd(USART1, ENABLE);                    																	//ʹ�ܴ���1 
		}

		
/************************************************************************************************************************************
                                                    USART�жϷ�����					
************************************************************************************************************************************/
 

			void USART1_IRQHandler(void)
			{
				u8 Rec;
				u8 Rec_H;
				u8 Rec_L;
				
				if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
				{
						Rec = USART_ReceiveData(USART1);	                 //��ȡ���յ�������
								
						answer=1;
						
						Rec_H=Rec>>4;
							
						if(stop_flag!=1)
						{
							switch (Rec_H)
							{
								case 0x0a:
									statu=1;
									time_out=0;
								  ACK=1;
									break;
								
								case 0x0b:
									statu=2;
									time_out=0;
								  ACK=1;
									break;
								
								case 0x0c:
									statu=3;
									time_out=0;
								  ACK=1;				
									break;
								
								case 0x0d:
									statu=4;
									time_out=0;
								  ACK=1;						
									break;
								
								default:
									ACK=0;
									break;
							}
						}
						
						USART_ClearFlag(USART1, USART_FLAG_RXNE);			
				} 
			}

#endif	


