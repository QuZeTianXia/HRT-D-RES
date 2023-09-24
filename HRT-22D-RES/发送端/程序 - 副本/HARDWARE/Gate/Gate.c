#include "Gate.h"

uint16_t duration=0;
uint8_t last_op=0;
uint8_t Present_op=0;
Gate_Type Gate[4] = {{Gate_OFF,0},{Gate_OFF,0},{Gate_OFF,0},{Gate_OFF,0}};

void GateCtInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;	          //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
	GateAll_OFF();
}

void Fresh_GatePower(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		if(Gate[i].Power==Gate_ON)
			PBout((i+5))=Gate_ON;
		else
			PBout((i+5))=Gate_OFF;
	}
}

uint8_t GenRandom(void)
{
			if((Flag_led<50)||(Flag_led>=50&&Flag_led<100))
				return 1;
			if((Flag_led>=100&&Flag_led<150)||(Flag_led>=150&&Flag_led<=200))
				return 2;				
			return 0;
}

/**************************************************************************
功能：单个门电源控制
参数：@ number 门编号；@ state 状态：Gate_ON，Gate_OFF
返回值：无
**************************************************************************/
void GatePower(uint8_t number,uint8_t state)
{
	Gate[number].Power=state;
	Fresh_GatePower();
	return;	
}

/**************************************************************************
功能：门电源全开
参数：
返回值：无
**************************************************************************/
void GateAll_ON(void)
{
	uint8_t i;
	for(i = 0;i < 4;i++)
	{
		Gate[i].Power=Gate_ON;
	}
	Fresh_GatePower();
	return;	
}

/**************************************************************************
功能：门电源全关
参数：
返回值：无
**************************************************************************/
void GateAll_OFF(void)
{
	uint8_t i;
	for(i = 0;i < 4;i++)
	{
		Gate[i].Power=Gate_OFF;
	}
	Fresh_GatePower();
	return;	
}

/**************************************************************************
功能：门通过记录清零
参数：
返回值：无
**************************************************************************/
void GateReClr(void)
{
	uint8_t i;
	for(i = 0;i < 4;i++)
	{
		Gate[i].passed=0;
	}
	return;	
}

/**************************************************************************
功能：门自动选择
参数：@ sta:0练习，1竞赛
返回值：无
**************************************************************************/
uint8_t GateAtSw(uint8_t sta)
{
	if(!sta)										//练习模式
	{	
		if(Gate[Present_op].passed)
		{
			GateAll_OFF();
			Beep_100MS(2);
			Present_op++;
			if(Present_op>3)
				Present_op=0;			
			GateReClr();
		}	
	GatePower(Present_op,Gate_ON);		
	}
	
	else if(sta)
	{		
		if(Gate[0].passed)
		{
			printf("pass");
			Beep_100MS(2);
			GateAll_OFF();
			Present_op=GenRandom();
			GateReClr();
		}
		
		if(Present_op==1||Present_op==2)
		{
				if(Gate[Present_op].passed)
			{
				printf("pass");
				Beep_100MS(2);
				GateAll_OFF();
				Present_op=3;
				//GatePower(Present_op,Gate_ON);
				GateReClr();
			}	
		}
				
		if(Gate[3].passed)
		{
			printf("stop");
			Beep_100MS(6);
			GateReClr();
			GateAll_OFF();
			s_key1=0;
			Present_op=0;			
			return 1;
		}	
		GatePower(Present_op,Gate_ON);		
	}
	else
		return 0;	
	return 1;
}
