#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"

float Voltage;
int voltage_first; 
int voltage_second; 
int voltage_third; 


void Battery_Monitor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	
	//GPIO����
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//ADC����
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(ADC1);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC ����ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	    //��ͨ��ģʽ(disable);��ͨ��ģʽ��enable)
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //����ת��ģʽ(disable);����ת��ģʽ��enable)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    //ADC �����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;                   //˳����й���ת���� ADC ͨ������Ŀ

	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);	//ʹ��ָ���� ADC1
	ADC_DMACmd(ADC1,ENABLE); //ʹ��DMA����
	
	ADC_ResetCalibration(ADC1);  //��λУ׼
	while(ADC_GetResetCalibrationStatus(ADC1)); //�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);  //ADУ׼
	while(ADC_GetCalibrationStatus(ADC1)); //�ȴ�ADУ׼����
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,1,ADC_SampleTime_239Cycles5);//ͨ�� 2,�������˳��ֵΪ 1,����ʱ��Ϊ 239.5 ����
}

uint16_t ADC_GetDate(void)
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);   //ʹ�����ת������
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1); //�������һ�� ADC1 �������ת�����
}


uint16_t Battery_Voltage(void)
{
	Voltage = ((float)ADC_GetDate()/4096*3.318)/3640*9770 ;
	voltage_first = (int)(Voltage  *  100) % 10;
	voltage_second = (int)(Voltage  *  10) % 10                                                                             ;
	voltage_third = (int)(Voltage) % 10;
	return voltage_third*100+voltage_second*10+voltage_first;
}



