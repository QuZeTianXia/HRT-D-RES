#ifndef BATTERY_VOLTAGE_H
#define BATTERY_VOLTAGE_H
#include "stm32f10x.h"                  // Device header

uint16_t ADC_GetDate(void);
void Battery_Monitor_Init(void);
uint16_t Battery_Voltage(void);

#endif

