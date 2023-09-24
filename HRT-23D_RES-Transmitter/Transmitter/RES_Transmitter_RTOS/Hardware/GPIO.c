#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"

void GPIOS_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;//LED
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
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

void RED_ON(void)
{
	GPIO_SetBits(RED_Port ,RED_Pin );	
}

void RED_OFF(void)
{
	GPIO_ResetBits(RED_Port ,RED_Pin );	
}

void BLUE_ON(void)
{
	GPIO_SetBits(BLUE_Port ,BLUE_Pin );	
}

void BLUE_OFF(void)
{
	GPIO_ResetBits(BLUE_Port ,BLUE_Pin );	
}

void GREEN_ON(void)
{
	GPIO_SetBits(GREEN_Port ,GREEN_Pin );	
}

void GREEN_OFF(void)
{
	GPIO_ResetBits(GREEN_Port ,GREEN_Pin );	
}

void YELLOW_ON(void)
{
	GPIO_SetBits(YELLOW_Port ,YELLOW_Pin );	
}

void YELLOW_OFF(void)
{
	GPIO_ResetBits(YELLOW_Port ,YELLOW_Pin );	
}



