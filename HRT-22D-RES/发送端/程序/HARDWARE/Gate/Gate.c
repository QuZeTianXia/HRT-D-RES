#include "Gate.h"

uint16_t duration=0;
uint8_t last_op=0;
uint8_t Present_op=0;
Gate_Type Gate[4] = {{Gate_OFF,0},{Gate_OFF,0},{Gate_OFF,0},{Gate_OFF,0}};

void GateCtInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ�ܶ˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;	          //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
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
���ܣ������ŵ�Դ����
������@ number �ű�ţ�@ state ״̬��Gate_ON��Gate_OFF
����ֵ����
**************************************************************************/
void GatePower(uint8_t number,uint8_t state)
{
	Gate[number].Power=state;
	Fresh_GatePower();
	return;	
}

/**************************************************************************
���ܣ��ŵ�Դȫ��
������
����ֵ����
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
���ܣ��ŵ�Դȫ��
������
����ֵ����
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
���ܣ���ͨ����¼����
������
����ֵ����
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
���ܣ����Զ�ѡ��
������@ sta:0��ϰ��1����
����ֵ����
**************************************************************************/
uint8_t GateAtSw(uint8_t sta)
{
	if(!sta)										//��ϰģʽ
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
