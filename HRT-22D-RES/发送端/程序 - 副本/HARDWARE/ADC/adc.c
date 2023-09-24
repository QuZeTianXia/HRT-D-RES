#include "adc.h"
#include "include.h"

#define ADC1_DR_Address (u32)(0x40012400+0x4c)     //DMA配置需要该ADC1地址
u16 ADCConvertedValue[MAX_AD]={0};
u16 AD_Value[MAX_AD] = {0};

#define AD_HISTORY_NUM 6 //如果这个数太大可能导致中断函数跑不过来 最后影响其他程序

uint16_t AD_Value_History[MAX_AD][AD_HISTORY_NUM];
uint32_t AD_Value_Total[MAX_AD] = {0};
uint8_t AD_Value_Rear[MAX_AD] = {0};



void DMA_ADC1_Init(void)
{
		ADC_InitTypeDef ADC_InitStructure;
	  DMA_InitTypeDef DMA_InitStructure;
		//使能DMA时钟
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	  /* DMA1 channel1 configuration ----------------------------------------------*/
	  DMA_DeInit(DMA1_Channel1);
	  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	  DMA_InitStructure.DMA_BufferSize = 1;           //ADC通道 几路AD就是几 
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable ;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	  
	  /* Enable DMA1 channel1 */
	  DMA_Cmd(DMA1_Channel1, ENABLE);
	  
	  /* ADC1 configuration ------------------------------------------------------*/
	  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfChannel = 1;  //顺序进行ADC转换的通道个数
	  ADC_Init(ADC1, &ADC_InitStructure);

	  /* ADC1 regular channel1.2 configuration */ 
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);   //A0 通道 转换次序 转换时间
	  //ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);   //A1
		//ADC_RegularChannelConfig(ADC1,ADC_Channel_8, 3, ADC_SampleTime_239Cycles5);   //B0
		//ADC_RegularChannelConfig(ADC1,ADC_Channel_9, 4, ADC_SampleTime_239Cycles5);   //B1
	  /* Enable ADC1 DMA */
	  ADC_DMACmd(ADC1, ENABLE);              
	  
	  /* Enable ADC1 */
	  ADC_Cmd(ADC1, ENABLE);            //使能ADC1

	  /* Enable ADC1 reset calibration register */   
	  ADC_ResetCalibration(ADC1);
	  /* Check the end of ADC1 reset calibration register */
	  while(ADC_GetResetCalibrationStatus(ADC1));

	  /* Start ADC1 calibration */
	  ADC_StartCalibration(ADC1);
	  /* Check the end of ADC1 calibration */
	  while(ADC_GetCalibrationStatus(ADC1));
	     
	  /* Start ADC1 Software Conversion */ 
	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void ADCdeal(void)
{
    char i = 0;
	  uint8_t Index_Temp;
	  for(;i <= MAX_AD - 1;++i)
	  {
				AD_Value_Total[i] = 0;
				AD_Value_History[i][AD_Value_Rear[i]] = ADCConvertedValue[i];
				++AD_Value_Rear[i];
				if(AD_Value_Rear[i] >= AD_HISTORY_NUM)
						AD_Value_Rear[i] = 0;
				for(Index_Temp = 0;Index_Temp < AD_HISTORY_NUM ; ++Index_Temp)	
				{
						AD_Value_Total[i] += AD_Value_History[i][Index_Temp];
				}
				AD_Value[i] = (AD_Value_Total[i]/AD_HISTORY_NUM); 
		}
		Batt_ad=AD_Value[0];
		
}
