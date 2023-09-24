#include "digitron.h"
#include "include.h"

uint16_t Dis_V=0;

void Digitron_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�ܶ˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	          //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA 
}

uint8_t Bit_table[]={
	//1    2    3    
	0xfe,0xfd,0xfb,                                          //λ��
};

uint8_t Seg_table[]={
// 0    1    2    3    4    5    6    7    8    9   
	0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,						// ����
// 0.		1.	 2.		3.   4.   5.   6.   7.   8.   9.
	0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,
};


/**************** ��HC595����һ���ֽں��� ******************/
void Send_595_Data(uint8_t dat)
{		
//	unsigned char	i;
////	HC595_ENABLE();          //hc595���ʹ��
//	for(i=0; i<8; i++)
//	{
//		if(dat & 0x80)
//		{
//			HC595_SR_DATA   = 1;
//		}
//		else
//		{
//			HC595_SR_DATA   = 0;
//		}		
//		HC595_SH_CLK = 1;
//		delay_us(1);
//		HC595_SH_CLK = 0;
//		dat <<= 1;
//		
//	}
}

/************************* ��ʾ���� ***************************/
void DisplayScan(uint8_t D_bit,uint8_t Val)
{	
//	Send_595_Data(Bit_table[D_bit]);	        	//���λ��
//	Send_595_Data(Seg_table[Val]);	       	 //�������

//	HC595_ST_CLK = 1;
//	delay_us(1);
//	HC595_ST_CLK = 0;							//�����������
}

/************************* ��ѹ��ʾ���� ***************************/
void Display_V(void)
{
//		uint8_t disp_bit=0;
		float Voltage;
//		uint8_t Shi,Ge,Xiao;

		Voltage=Batt_ad*0.02578; 
		Dis_V= (uint16_t)Voltage+4;
//		Xiao=Dis_V%10;
//		Ge=(Dis_V/10)%10;
//		Shi=Dis_V/100;
//		for(disp_bit=0;disp_bit<2;disp_bit++)
//				{						
//					switch (disp_bit){
//						case 0:
//							DisplayScan(disp_bit,Xiao);
//						  delay_ms(1);
//							break;
//					 	case 1:
//							DisplayScan(disp_bit,(Ge+10));
//					 	  delay_ms(1);
//							break;
//						case 2:
//							DisplayScan(disp_bit,Shi);
//				 		  delay_ms(1);
//							break;
//						default: break;
//						}
//					}
}
	
