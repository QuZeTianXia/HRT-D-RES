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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE); //ʹ�ܶ˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	          //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	          //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 	
	MD0=0;
	MD1=0;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�ܶ˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	          //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
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
//	USART_SendData(USART1, 0x19);														//ͨ���ŵ�
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
