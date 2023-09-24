#ifndef __DIGITRON_H
#define __DIGITRON_H			  	 
#include "sys.h"
#include "delay.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
//-----------------OLED端口定义---------------- 
#define POWER3 PBout(4)   //使能

#define POWER2 PBout(5)    //锁存时钟信号

#define POWER1 PBout(6)  	  //移位时钟信号

#define POWER4 PBout(3)   //数据脚

//OLED控制用函数
void Digitron_init(void);	    
void Send_595_Data(uint8_t dat);
void DisplayScan(uint8_t D_bit,uint8_t Val);
void Display_V(void);

extern uint16_t Dis_V;
#endif  
	 
