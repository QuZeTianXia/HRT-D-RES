#ifndef __BUZZER_H
#define __BUZZER_H
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
//LED �˿ڶ���
#define Bell PAout(12) // PA12
void Bell_Init(void);  //��ʼ��
void Beep_100MS(uint8_t hd_ms);
void TIM4_IRQHandler(void);

extern uint8_t beep_count;
#endif
