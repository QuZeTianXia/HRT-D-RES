#ifndef __AS32_H
#define __AS32_H
#include "sys.h"


//LED �˿ڶ���
#define MD0 PBout(15) 
#define MD1 PBout(14)
#define AUX PBin(13)

void AS32_Init(void);  //��ʼ��
void AS32_Send(uint16_t add,uint8_t data);
#endif
