#ifndef __TIMER_H
#define __TIMER_H
#include <sys.h>	 


void TIM3_IT_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);
void Timing(void);

extern uint8_t count_ms;
extern uint8_t sec,min,hr;
extern uint8_t time_out;
extern uint8_t answer;
extern uint8_t stop_flag;
extern uint8_t wireless_sta;

#endif
