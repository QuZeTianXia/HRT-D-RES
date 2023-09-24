#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"

uint16_t RES_Receiver_State = 1;
//uint16_t Vehicle_State_Msg[8];
uint8_t  Vehicle_State_Flag = 0;
uint8_t  Msg_count = 0;
uint16_t Offline_count = 0;
uint8_t  Offline_Flag = 0;//定义1为下线。0为连接
uint8_t RES_STATE = Emergency_Stop ;
uint8_t Old_RES_STATE = Emergency_Stop;
int State_Error = 0;
uint8_t State_Switch_Count = 0;

void Lora_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	//TX
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//M0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//M1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //流控制关
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;                    //收发模式
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //无奇偶校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //一个停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //字长为 8 位数据格式
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//IT
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ;           //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                    //子优先级       
	NVIC_Init(&NVIC_InitStructure);
}

void Lora_SendByte(uint16_t Data)//串口发送字符函数封装
{
		 USART_SendData(USART1,Data);//串口1发送字符0
		 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//如果数据寄存器空标志位为空，则已经成功发送数据跳出
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		
		Offline_count = 1;		
		RES_Receiver_State = USART_ReceiveData(USART1);
        Lora_SendByte(RES_STATE);//串口发送字符函数封装
 
	}
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
}


//int fputc(int ch, FILE *f)
//{
//    /* 发送一个字节数据到串口 */
//    USART_SendData(USART1, (uint8_t)ch);

//    /* 等待发送完毕 */
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
