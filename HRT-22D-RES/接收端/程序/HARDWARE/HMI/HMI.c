#include "HMI.h"


void HMI_SendCmd(const uint8_t *cmd,uint16_t val)
{
	uint8_t i;
	printf("%s=%d",cmd,val);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);
	
	for(i=0;i<3;i++)
	{
		USART_SendData(USART1, 0xff);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);
	}
}


void HMI_Init(void)
{
	uint8_t i;
	uart_init(9600);
	printf("page 2");
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);
	for(i=0;i<3;i++)
	{
		USART_SendData(USART1, 0xff);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);
	}
}
