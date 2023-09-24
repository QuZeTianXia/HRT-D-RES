#ifndef __BUZZER_H
#define __BUZZER_H
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
//LED 端口定义
#define Bell PAout(12) // PA12
void Bell_Init(void);  //初始化
void Beep_100MS(uint8_t hd_ms);
void TIM4_IRQHandler(void);

extern uint8_t beep_count;
#endif
