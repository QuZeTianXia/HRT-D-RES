#ifndef __TIMER_H
#define __TIMER_H
#include <sys.h>	 
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

void TIM3_IT_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);
void Timing(void);

extern uint8_t count_ms;
extern uint8_t sec,min,hr;
extern uint8_t TR_flag;
extern uint8_t TR_count;
extern uint8_t EMR;
extern uint8_t car_statu;

#endif
