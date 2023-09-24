#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"

float Voltage;
int voltage_first; 
int voltage_second; 
int voltage_third; 


void Battery_Monitor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	
	//GPIO配置
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//ADC配置
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(ADC1);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC 独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	    //单通道模式(disable);多通道模式（enable)
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //单次转换模式(disable);连续转换模式（enable)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    //ADC 数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;                   //顺序进行规则转换的 ADC 通道的数目

	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);	//使能指定的 ADC1
	ADC_DMACmd(ADC1,ENABLE); //使能DMA传输
	
	ADC_ResetCalibration(ADC1);  //复位校准
	while(ADC_GetResetCalibrationStatus(ADC1)); //等待复位校准结束
	ADC_StartCalibration(ADC1);  //AD校准
	while(ADC_GetCalibrationStatus(ADC1)); //等待AD校准结束
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,1,ADC_SampleTime_239Cycles5);//通道 2,规则采样顺序值为 1,采样时间为 239.5 周期
}

uint16_t ADC_GetDate(void)
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);   //使能软件转换功能
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1); //返回最近一次 ADC1 规则组的转换结果
}


uint16_t Battery_Voltage(void)
{
	Voltage = ((float)ADC_GetDate()/4096*3.318)/3640*9770 ;
	voltage_first = (int)(Voltage  *  100) % 10;
	voltage_second = (int)(Voltage  *  10) % 10                                                                             ;
	voltage_third = (int)(Voltage) % 10;
	return voltage_third*100+voltage_second*10+voltage_first;
}



