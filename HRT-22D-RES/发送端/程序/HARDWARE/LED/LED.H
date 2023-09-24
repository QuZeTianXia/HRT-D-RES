#ifndef __LED_H
#define __LED_H
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
//LED 端口定义
#define Link_LED PAout(4) 
#define Stop_LED PAout(3) 
#define Ready_LED PAout(6) 
#define Run_LED PAout(5) 

void LED_Init(void);  //初始化

#endif
