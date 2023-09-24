#include "e22.h"
#include "usart.h"
#include "delay.h"

/************************************************************************************************************************************
                                                      无线通讯模块初始化				
************************************************************************************************************************************/	
		
			
/************************************************************************************************************************************
			                                                 无线通讯模块发送				
************************************************************************************************************************************/
			
			void E22_Send(uint16_t add,uint8_t data)
			{
	
						USART_SendData(USART1, data);                            
						while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)!=SET);  
						USART_SendData(USART1, data);
						while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)!=SET);
						USART_SendData(USART1, data);														  
						while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)!=SET);
						USART_SendData(USART1, data);
						while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);   
				
			}

