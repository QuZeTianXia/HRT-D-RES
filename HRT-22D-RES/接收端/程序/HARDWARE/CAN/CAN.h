#ifndef __CAN_H
#define __CAN_H

#include "sys.h"

//CAN接收RX0中断使能
#define CAN_RX0_INT_ENABLE	1		//0,不使能;1,使能.	

uint8_t CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);
uint8_t Can_Send_Msg(u16 std_id,u8* msg,u8 len);
uint8_t Can_Receive_Msg(u8 *buf);
extern uint8_t ECU_conneted;

#endif
