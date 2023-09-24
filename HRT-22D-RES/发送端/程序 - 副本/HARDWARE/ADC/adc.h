#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

#define MAX_AD 1

extern u16 ADCConvertedValue[MAX_AD];
extern u16 AD_Value[MAX_AD];


void DMA_ADC1_Init(void);
void ADCdeal(void);


#endif 















