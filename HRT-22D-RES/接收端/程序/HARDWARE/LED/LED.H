#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED 端口定义
#define SysSta PBout(13) 
#define SysCom PBout(14)
#define Relay  PBout(9)
#define Relay2 PBout(8)

void LED_Init(void);  //初始化
void Led_Flash(u16 time);
#endif
