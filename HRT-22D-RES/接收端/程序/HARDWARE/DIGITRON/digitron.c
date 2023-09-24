#include "include.h"

void Digitron_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	          //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;     //10M
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
	DisplayScan(10,0);
}

uint16_t c_table[5][11]={
	{// 	0			1			2		 		3		 	4		 		5				6   	7   	 8   		 9    10   	EX0
		0xffff,0xfffe,0xfffc,0xfff8,0xfff0,0xffe0,0xffc0,0xff80,0xff00,0xfe00,0xfc00},
	
	{// 	0			1			2		 		3		 	4		 		5				6   	7   	 8   		 9    10   	EX1		
		0xfbff,0xfbfe,0xfbfc,0xfbf8,0xfbf0,0xfbe0,0xfbc0,0xfb80,0xfb00,0xfa00,0xf800},

	{// 	0			1			2		 		3		 	4		 		5				6   	7   	 8   		 9    10   	EX2
		0xf7ff,0xf7fe,0xf7fc,0xf7f8,0xf7f0,0xf7e0,0xf7c0,0xf780,0xf700,0xf600,0xf400},
	
	{// 	0			1			2		 		3		 	4		 		5				6   	7   	 8   		 9    10   	EX3
		0xefff,0xeffe,0xeffc,0xeff8,0xeff0,0xefe0,0xefc0,0xef80,0xef00,0xee00,0xec00},
	
	{// 	0			1			2		 		3		 	4		 		5				6   	7   	 8   		 9    10   	EX4
		0xdfff,0xdffe,0xdffc,0xdff8,0xdff0,0xdfe0,0xdfc0,0xdf80,0xdf00,0xde00,0xdc00},
};


/**************** 向HC595发送一个字节函数 ******************/
void Send_595_Data(uint8_t dat)
{		
	unsigned char	i;
	HC595_ENABLE();          //hc595输出使能
	for(i=0; i<8; i++)
	{
		if(dat & 0x80)
		{
			HC595_SR_DATA   = 1;
		}
		else
		{
			HC595_SR_DATA   = 0;
		}		
		HC595_SH_CLK = 1;
		delay_us(1);
		HC595_SH_CLK = 0;
		dat <<= 1;
		
	}
}
/************************* 显示函数 ***************************/
void DisplayScan(uint8_t EX,uint8_t Power)
{	
	uint8_t table1,table2;
	table1=c_table[EX][Power]>>8;
	table2=c_table[EX][Power]&0xff;
	Send_595_Data(table1);	        	//输出段码
	Send_595_Data(table2);	       	 //输出段码

	HC595_ST_CLK = 1;
	delay_us(1);
	HC595_ST_CLK = 0;							//锁存输出数据
}
