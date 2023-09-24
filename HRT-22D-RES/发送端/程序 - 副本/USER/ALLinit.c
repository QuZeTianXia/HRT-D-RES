#include "include.h"

void All_Init(void)
{
	delay_init();	
	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);            //=====����NVIC����
	LED_Init();
	Digitron_init();
	Key_EXTI_Init();
	DMA_ADC1_Init();
	AS32_Init();
	delay_ms(320);
	TIM3_IT_Init(99,7199);					//10ms
		//OLED_Init();
	
}

