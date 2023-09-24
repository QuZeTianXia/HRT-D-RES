#include "include.h"

void All_Init(void)
{
	delay_init();	
	JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);            //=====进行NVIC分组
	LED_Init();
	Digitron_init();
	Key_EXTI_Init();
	DMA_ADC1_Init();
	AS32_Init();
	delay_ms(320);
	TIM3_IT_Init(99,7199);					//10ms
		//OLED_Init();
	
}

