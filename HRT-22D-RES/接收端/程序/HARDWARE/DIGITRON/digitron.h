#ifndef __DIGITRON_H
#define __DIGITRON_H			  	 
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
//-----------------OLED�˿ڶ���---------------- 
#define HC595_ENABLE() PBout(12)=0   //ʹ��
#define HC595_DISABLE() PBout(12)=1   //ʧ��

#define HC595_ST_CLK PBout(13)    //����ʱ���ź�

#define HC595_SH_CLK PBout(14)  	  //��λʱ���ź�

#define HC595_SR_DATA  PBout(15)   //���ݽ�

//OLED�����ú���
void Digitron_init(void);	    
void Send_595_Data(uint8_t dat);
void DisplayScan(uint8_t EX,uint8_t Power);

#endif  
	 
