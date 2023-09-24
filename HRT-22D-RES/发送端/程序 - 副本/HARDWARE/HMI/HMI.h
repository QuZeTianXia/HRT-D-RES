#ifndef __HMI_H
#define __HMI_H
#include "sys.h"
#include "usart.h"

void HMI_SendCmd(const uint8_t *cmd,uint16_t val);
void HMI_Init(void);


#endif
