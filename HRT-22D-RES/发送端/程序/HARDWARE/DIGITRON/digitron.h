#ifndef __DIGITRON_H
#define __DIGITRON_H			  	 
#include "sys.h"
#include "delay.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
//-----------------OLED�˿ڶ���---------------- 
#define POWER3 PBout(4)   //ʹ��

#define POWER2 PBout(5)    //����ʱ���ź�

#define POWER1 PBout(6)  	  //��λʱ���ź�

#define POWER4 PBout(3)   //���ݽ�

//OLED�����ú���
void Digitron_init(void);	    
void Send_595_Data(uint8_t dat);
void DisplayScan(uint8_t D_bit,uint8_t Val);
void Display_V(void);

extern uint16_t Dis_V;
#endif  
	 
