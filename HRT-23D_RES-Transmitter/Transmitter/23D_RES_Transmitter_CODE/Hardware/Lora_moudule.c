#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"

extern uint16_t RX_TEXT;

void Lora_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	//TX
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//M0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//M1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //�����ƹ�
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;                    //�շ�ģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //����żУ��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //һ��ֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //�ֳ�Ϊ 8 λ���ݸ�ʽ
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//IT
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;           //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                  //�����ȼ�       
	NVIC_Init(&NVIC_InitStructure);
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
//		OLED_ShowNum(0,16,USART_ReceiveData(USART1),3,16,1);
		RX_TEXT = USART_ReceiveData(USART1);		
	}
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
}

void Lora_SendByte(uint16_t Data)//���ڷ����ַ�������װ
{
		 USART_SendData(USART1,Data);//����1�����ַ�0
		 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//������ݼĴ����ձ�־λΪ�գ����Ѿ��ɹ�������������
}
//int fputc(int ch, FILE *f)
//{
//    /* ����һ���ֽ����ݵ����� */
//    USART_SendData(USART1, (uint8_t)ch);

//    /* �ȴ�������� */
//    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

//    return (ch);
//}


void Lora_Normal_Mode(void)
{
	GPIO_ResetBits(Lora_M0_Port,Lora_M0_Pin);
	GPIO_ResetBits(Lora_M1_Port,Lora_M1_Pin);
}

void Lora_PowerSaving_Mode(void)
{
	GPIO_ResetBits(Lora_M0_Port,Lora_M0_Pin);
	GPIO_SetBits(Lora_M1_Port,Lora_M1_Pin);
}

void Lora_WakeUp_Mode(void)
{
	GPIO_SetBits(Lora_M0_Port,Lora_M0_Pin);
	GPIO_ResetBits(Lora_M1_Port,Lora_M1_Pin);
}

void Lora_Sleep_Mode(void)
{
	GPIO_SetBits(Lora_M0_Port,Lora_M0_Pin);
	GPIO_SetBits(Lora_M1_Port,Lora_M1_Pin);
}
