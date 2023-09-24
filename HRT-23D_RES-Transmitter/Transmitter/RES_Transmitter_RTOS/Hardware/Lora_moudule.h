#ifndef LORA_MOUDULE_H
#define LORA_MOUDULE_H
#include "stm32f10x.h"                  // Device header

void Lora_Init(void);
void Lora_SendByte(uint16_t Data);//串口发送字符函数封装
void Lora_Normal_Mode(void);	
void Lora_PowerSaving_Mode(void);
void Lora_WakeUp_Mode(void);
void Lora_Sleep_Mode(void);



#endif

