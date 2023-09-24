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
uint8_t wireless_sta=0;			//0:通讯断开 1:通讯连接
uint8_t can_count=0;
uint8_t stop_count=0;
uint8_t send_count=0;
uint8_t buf[8];
extern uint8_t ECU_conneted;

/************************************************************************************************************************************
                                                       定时器3定时中断初始化				
************************************************************************************************************************************/
			
			
			void TIM3_IT_Init(u16 arr,u16 psc)	
			{	 				
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				NVIC_InitTypeDef NVIC_InitStructure;

				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	      //使能TIM3时钟
					
				//初始化定时器3 TIM3 
				TIM_TimeBaseStructure.TIM_Period = arr;                     //设定计数器自动重装值 
				TIM_TimeBaseStructure.TIM_Prescaler =psc; 	                //预分频器   
				TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
				TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
				TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                    //允许更新中断
				
				//中断分组初始化
				NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;             //TIM3中断
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //先占优先级1级
				NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  				//从优先级0级
				NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 						//IRQ通道被使能
				NVIC_Init(&NVIC_InitStructure); 														//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
			
				TIM_Cmd(TIM3, ENABLE); 	                                    //使能定时器3			
			}

			
/************************************************************************************************************************************
                                                       定时器2中断服务函数				
************************************************************************************************************************************/
			

void TIM3_IRQHandler(void)                                    //定时器中断服务函数
{ 		    		  			    
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)              //中断被触发	
	{
		uint8_t CAN_msg[8];
		uint8_t E22;
		
		count_ms++;
		time_out++;
		can_count++;
		
		if(timer>0)
			timer--;
			
					
/************************************************************************************************************************************
                                                           CAN通讯				
************************************************************************************************************************************/					


				if((count_ms%9)==0)
				{
					switch (statu)
					{
						case 1:
							CAN_msg[0]=0x00;   //制动 00000000
							break;
						
						case 2:
							CAN_msg[0]=0xa8;   //准备 10101000
							break;
						
						case 3:
							CAN_msg[0]=0xf8;   //缓停 11111000
							break;
						
						case 4:
							CAN_msg[0]=0xd0;   //运行 11010000
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
							  {CAN_msg[0]=CAN_msg[0]+0x03;}	   //发射端、ECU同时断线
						  else
					      {CAN_msg[0]=CAN_msg[0]+0x01;}    //ECU断线
				    }
						
					else if(stop_flag==1)
						     CAN_msg[0]=CAN_msg[0]+0x02;     //发射端断线
					
					Can_Send_Msg(0x117,CAN_msg,1);
					
				}
						

/************************************************************************************************************************************
					                                                无线通讯发送				
************************************************************************************************************************************/					
					
					
				if(ACK==1&&answer==1&&timer==0&&stop_flag==0)               //命令发送结束后，计时160ms
						{                                                       //时间之内接收到请求恢复状态两次，隔60ms
							switch (statu)
							{
								case 1:
									E22=0xab;   //制动
									break;
								
								case 2:
									E22=0xcc;   //准备
									break;
								
								case 3:
									E22=0x66;   //缓停
									break;
								
								case 4:
									E22=0x3f;   //运行
									break;
								
								default:
									E22=0xab;
								break;
							}
							
							E22_Send(0x4e7a,E22);		                              //发送车的状态	
								
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
					                                                 超时断开				
************************************************************************************************************************************/

				
				if(time_out>=100)                                 //超时1秒后断开
					{
						statu=1;
						wireless_sta=0;
						stop_flag=1;						
					}

					
				if(stop_flag)                                       
					{
						stop_count++;
					}
			
				if(stop_count>150)                                         //断线停车后1.5s后结束停止警告
					{
						stop_flag=0;
						time_out=0;
						stop_count=0;
					}		

					
					
/************************************************************************************************************************************
                                                        LED信号灯指示				
************************************************************************************************************************************/					

				
				if(wireless_sta)                                           //接收到无线通讯
					{
						if(Rec_count>=1)   
							{
								SysCom=0;                                          //LED2亮
								Rec_count=0;
								answer=1;
								ACK=0;
							}  		
					}
				
				if(wireless_sta==0)                                        //未接收到无线通讯，LED2灭
						SysCom=1;
				
			if(count_ms==50||count_ms==100)                            //LED1闪烁，指示程序正常运行
					  SysSta=~SysSta; 

				
				Timing();
					
				TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                 //清除中断标志位 						
	}
			      
}

/************************************************************************************************************************************
					                                                   计时器				
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



