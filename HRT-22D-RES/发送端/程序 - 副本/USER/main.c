#include "include.h"
#include "digitron.h"
uint8_t test=0;
uint16_t Batt_ad;


int main(void)
 {
		All_Init();
		while(1)
		{
		Display_V();
//			Communicate();
			/*if(TR_flag)
			{
				TR_flag=0;
				AS32_Send(0x6e);
			}

			if(Rec_count>=10)
			{
				OLED_ShowString(12,12,"         ");
				OLED_ShowString(12,2,"LINKED");
				OLED_ShowNumber(12,22,test,3,16);
				OLED_ShowNumber(12,42,Rec_count,3,16);
				AS32_Send("Total",test);
			}
			else
				OLED_ShowString(12,12,"         "),
				OLED_ShowString(12,12,"Off_Line!");
				
				Rec_count=0;
				OLED_Refresh_Gram();
			}*/
		}
	
 }
