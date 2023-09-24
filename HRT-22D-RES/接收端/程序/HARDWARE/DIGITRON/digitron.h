#ifndef __DIGITRON_H
#define __DIGITRON_H			  	 
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
//-----------------OLED端口定义---------------- 
#define HC595_ENABLE() PBout(12)=0   //使能
#define HC595_DISABLE() PBout(12)=1   //失能

#define HC595_ST_CLK PBout(13)    //锁存时钟信号

#define HC595_SH_CLK PBout(14)  	  //移位时钟信号

#define HC595_SR_DATA  PBout(15)   //数据脚

//OLED控制用函数
void Digitron_init(void);	    
void Send_595_Data(uint8_t dat);
void DisplayScan(uint8_t EX,uint8_t Power);

#endif  
	 
