#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
//#define INT PBin(5)   //PB5连接到MPU6050的中断引脚
#define GateSig1 PAin(0)
#define GateSig2 PAin(1)
#define GateSig3 PAin(2)
#define GateSig4 PAin(3)

#define Key1 PAin(6)
#define Key2 PAin(7)

void Key_EXTI_Init(void);	//外部中断初始化		 	
void Gate_EXTI_Init(void);

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
#endif

























