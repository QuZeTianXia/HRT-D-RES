#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
//#define INT PBin(5)   //PB5���ӵ�MPU6050���ж�����
#define GateSig1 PAin(0)
#define GateSig2 PAin(1)
#define GateSig3 PAin(2)
#define GateSig4 PAin(3)

#define Key1 PAin(6)
#define Key2 PAin(7)

void Key_EXTI_Init(void);	//�ⲿ�жϳ�ʼ��		 	
void Gate_EXTI_Init(void);

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
#endif

























