#include "led.h"

/************************************************************************************************************************************
                                                       LED端口初始化				
************************************************************************************************************************************/	
			
			void LED_Init(void)
			{
				GPIO_InitTypeDef GPIO_InitStructure;
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    //使能端口时钟
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_8|GPIO_Pin_9;	 //端口配置
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;        //10M
				GPIO_Init(GPIOB, &GPIO_InitStructure);					         //根据设定参数初始化GPIOB 
				
				SysSta=1;//PB13
				SysCom=1;//PB14
				Relay=1;//PB9
				Relay2=1;//PB8

				
			}
