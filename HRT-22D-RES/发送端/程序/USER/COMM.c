#include "COMM.h"

uint8_t statu=1; //1:stop 2:ready 3:run
uint8_t wireless_sta=0;

void Communicate(void)
{
	if(wireless_sta==0)
		statu=1;
}
