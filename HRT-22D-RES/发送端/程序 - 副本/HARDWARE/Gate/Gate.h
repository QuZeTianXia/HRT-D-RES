#ifndef __GATE_H
#define __GATE_H	 
#include "sys.h"
  /**************************************************************************
×÷Õß£ºKirin
**************************************************************************/
#define Gate_ON 0
#define Gate_OFF 1

/*#define Gate_0_Ct PBout(5)
#define Gate_1_Ct PBout(6)
#define Gate_2_Ct PBout(7)
#define Gate_3_Ct PBout(8)*/

typedef
struct{
		uint8_t Power;
		uint8_t passed;
}Gate_Type;

extern Gate_Type Gate[4];
extern uint16_t duration;
extern uint8_t last_op;
extern uint8_t Present_op;

void GateCtInit(void);
void GateAll_ON(void);
void GatePower(uint8_t number,uint8_t state);
void GateAll_OFF(void);
void GateReClr(void);
void Fresh_GatePower(void);
uint8_t GateAtSw(uint8_t sta);


uint8_t GenRandom(void);
	
#endif
