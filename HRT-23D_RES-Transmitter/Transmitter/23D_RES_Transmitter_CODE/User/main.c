#include "stm32f10x.h"                  // Device header
#include "oled.h"  
#include "bmp.h" 
#include "Global_variable.h"
uint16_t RX_TEXT = 0;

int main(void)
{	
	GPIOS_Init();
	KEY_Init();
	Timer_Init();
	OLED_Init();
	Battery_Monitor_Init();
	Lora_Init();
	Lora_Normal_Mode();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //禁用JTAG
	
	
//	OLED_ColorTurn(1);//0正显示，1 反色显示
//	OLED_DisplayTurn(1);//0正常显示 1 屏幕翻转显示
//	OLED_Refresh();
	OLED_ShowPicture(0,0,128,32,BMP2,1);//HRT_LOGO
	OLED_Refresh();
	Delay_ms(1000);	
	OLED_Clear();
	OLED_ShowChinese(3,0,0,20,1);//遥
	OLED_ShowChinese(23,0,1,20,1);//控
	OLED_ShowChinese(43,0,2,20,1);//急
	OLED_ShowChinese(63,0,3,20,1);//停
	OLED_ShowChinese(83,0,4,20,1);//系
	OLED_ShowChinese(103,0,5,20,1);//统
	OLED_ShowString(80,55,"By QZTX",8,1);
	OLED_Refresh();
	Delay_ms(1000);	
	OLED_Clear();
	OLED_ShowChinese(0,0,0,12,1);//已
	OLED_ShowChinese(12,0,1,12,1);//连
	OLED_ShowChinese(24,0,2,12,1);//接
	OLED_ShowChinese(50,0,3,12,1);//电
	OLED_ShowChinese(62,0,4,12,1);//池
	OLED_ShowChinese(74,0,3,12,1);//电
	OLED_ShowChinese(86,0,5,12,1);//压
	OLED_ShowNum(99,0,third,1,12,1);
	OLED_ShowChar(105,0,'.',12,1);
	OLED_ShowNum(108,0,second,1,12,1);
	OLED_ShowNum(114,0,first,1,12,1);
	OLED_ShowChar(120,0,'V',12,1);
	OLED_Refresh();
	while (1)
	{
	//	OLED_ShowPicture(0,0,128,32,BMP2,1);
//		Battery_Voltage();
//		
//		OLED_ShowNum(99,0,third,1,12,1);
//		OLED_ShowNum(108,0,second,1,12,1);
//		OLED_ShowNum(114,0,first,1,12,1);
//OLED_ShowNum(0,16,RX_TEXT,3,16,1);
//		OLED_Refresh();
////		OLED_ShowNum(0,16,num,3,16,1);	
////		OLED_Refresh();
//		Lora_SendByte(0xB0);//串口发送字符函数封装
////		OLED_ShowNum(0,0,(uint16_t)Battery_Voltage(),5,16,1);	
////		OLED_ShowNum(0,16,GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3),2,16,1);
////		OLED_ShowNum(32,48,GPIO_ReadInputDataBit(STOP_Port,STOP_Pin),2,16,1);
////		OLED_ShowNum(64,80,GPIO_ReadInputDataBit(GO_Port,GO_Pin),2,16,1);
//		
		BEEP_ON();
		Delay_ms(500);
		BEEP_OFF();
		Delay_ms(500);		
		

	}
}
