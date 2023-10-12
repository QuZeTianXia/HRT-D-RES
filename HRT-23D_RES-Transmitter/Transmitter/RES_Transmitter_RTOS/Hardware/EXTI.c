#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"

int SWITCH_KEY_Flag = 0;
int GO_Key_Flag = 0;
int GO_Key_Count = 0;
int Old_GO_Key_Flag = 0;
int GO_Key_End = 0;
uint8_t GO_Exit_Flag = 1;

void KEY_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line3|EXTI_Line4|EXTI_Line5;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_Initstructure);
	

	NVIC_Initstructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 8;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_Initstructure);
	
	NVIC_Initstructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 7;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_Initstructure);
}


void EXTI3_IRQHandler(void)//SWITCH_KEY
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)
	{
		for(int i=0;i<3;i++)
		{
			Lora_SendByte(RES_STATE);
			i++;
		}
		 		
		EXTI_ClearITPendingBit(EXTI_Line3);
	}	
}

void EXTI4_IRQHandler(void)//GO_KEY
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
//		if(!Offline_Flag && RES_STATE == Ready)
//		{
//			
//		}

		Old_GO_Key_Flag = GO_Key_Flag;
		if(Go_Key_State == 0) GO_Key_Flag = 0;
		else GO_Key_Flag = 1;
		GO_Exit_Flag = 1;
		
		EXTI_ClearITPendingBit(EXTI_Line4);
	}	
}

void EXTI9_5_IRQHandler(void)//STOP_KEY
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{

		
		if(Stop_Key_State)
		{
			Old_RES_STATE = RES_STATE ;
			RES_STATE = Emergency_Stop ;
			State_Switch_Count = 1;
			State_Error = 0;
		}
		else 
		{
			if(!Offline_Flag)
			{
				Old_RES_STATE = RES_STATE ;
				RES_STATE = Ready;
				State_Switch_Count = 1;
			    State_Error = 0;
			}
			else 
			{
				Old_RES_STATE = RES_STATE ;
				RES_STATE = Emergency_Stop ;
				State_Switch_Count = 1;
			    State_Error = 0;
			}
		}

		EXTI_ClearITPendingBit(EXTI_Line5);
	}	
}
