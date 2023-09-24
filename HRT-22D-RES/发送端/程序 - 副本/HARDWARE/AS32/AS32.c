#include "AS32.h"
#include "usart.h"
#include "delay.h"
uint8_t limit=0;
uint8_t add_H;
uint8_t add_L;
void AS32_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	uart_init(9600);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE); //使能端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	          //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	          //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 	
	MD0=0;
	MD1=0;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	          //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
	while(AUX==0);
	
}

void AS32_Send(uint16_t add,uint8_t data)
{
//	add_H=(add >> 8);
//  add_L=(add & 0x00ff);
	
//	USART_SendData(USART1, add_H);
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)!=SET);
//	USART_SendData(USART1, add_L);
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)!=SET);
//	USART_SendData(USART1, 0x19);														//通信信道
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)!=SET);	
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);
}
