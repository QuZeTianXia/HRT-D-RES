#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"

void GPIOS_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	
}

void BEEP_Flash(void)
{
	if(GPIO_ReadOutputDataBit(BEEP_Port ,BEEP_Pin )==1)
	{
		GPIO_ResetBits(BEEP_Port ,BEEP_Pin );		
	}
	else
	{
		GPIO_SetBits(BEEP_Port ,BEEP_Pin );		
	}
}

void BEEP_ON(void)
{	
	GPIO_SetBits(BEEP_Port ,BEEP_Pin );		
	
}

void BEEP_OFF(void)
{	
	GPIO_ResetBits(BEEP_Port ,BEEP_Pin );		
	
}
