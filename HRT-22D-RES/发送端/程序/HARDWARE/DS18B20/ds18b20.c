#include "ds18b20.h"
#include "delay.h"

/******************************************
�������ƣ�GPIO_DQ_Out_Mode
��    �ܣ�����DQ����Ϊ��©���ģʽ
��    ������
����ֵ  ����
*******************************************/
void GPIO_DQ_Out_Mode(void)
{
    
  GPIO_InitTypeDef GPIO_InitStructure;
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�ܶ˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	          //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;      //��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
}
/******************************************
�������ƣ�GPIO_DQ_Input_Mode
��    �ܣ�����DQ����Ϊ��������ģʽ
��    ������
����ֵ  ����
*******************************************/
void GPIO_DQ_Input_Mode(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�ܶ˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	          //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
}
/******************************************
�������ƣ�Tx_ResetPulse
��    �ܣ����͸�λ����
��    ������
����ֵ  ����
*******************************************/
void Tx_ResetPulse(void)
{
    GPIO_DQ_Out_Mode() ;
    DQ_Write_0() ;  //��λ����
    delay_us(500) ; //���ٱ���480us
    DQ_Write_1() ;  //�����������ٶ�
    delay_us(1) ;
}
/******************************************
�������ƣ�Rx_PresencePulse
��    �ܣ�����Ӧ���ź�
��    ������
����ֵ  ����
*******************************************/
void Rx_PresencePulse(void)
{
    GPIO_DQ_Input_Mode() ;
    while( DQ_ReadBit()) ;  //�ȴ�DS18b20Ӧ��
    while( DQ_ReadBit() == 0) ; //DS18b20����������60~240us ,Ȼ��������������������
    delay_us(300);
    GPIO_DQ_Out_Mode() ;    //������ɣ��������¿�������
}
/******************************************
�������ƣ�Write_OneByte_ToDS18b20
��    �ܣ�дһ���ֽڵ�DS18b20
��    ������
����ֵ  ����
*******************************************/
void Write_OneByte_ToDS18b20(unsigned char data)
{
    unsigned char i ;
    GPIO_DQ_Out_Mode() ;
    for(i=0 ;i<8 ;i++)
    {
        if(data&0x01)    //��λ��ǰ
        {
            //д1
            DQ_Write_0() ; //дʱ���϶���Ǵ����ߵĵ͵�ƽ��ʼ
            delay_us(8) ;  //15us������
            DQ_Write_1() ;
            delay_us(80) ; //����д1ʱ϶������60us
        }
        else
        {
            //д0
            DQ_Write_0() ;
            delay_us(90) ; //������60us��120us֮��
            DQ_Write_1() ;
            delay_us(5) ;
        }
        data >>= 1 ;
    }
}
/******************************************
�������ƣ�Read_OneByte_FromDS18b20
��    �ܣ���DS18b20��һ���ֽ�
��    ������
����ֵ  ������������
*******************************************/
unsigned char Read_OneByte_FromDS18b20(void)
{
    unsigned char i ,data = 0 ;
    
    for(i=0 ;i<8 ;i++)
    {
        GPIO_DQ_Out_Mode() ;
        data >>= 1 ;
        DQ_Write_0() ;
        delay_us(2) ;
        GPIO_DQ_Input_Mode() ;
        delay_us(1) ;
        if(DQ_ReadBit())
        {
            data |= 0x80 ;
        }
        delay_us(70) ;   //�ȴ���һλ������ɴ���
    }
    GPIO_DQ_Out_Mode() ;
    return data ;
}
/******************************************
�������ƣ�Read_Temperature
��    �ܣ���ȡ�¶���Ϣ
��    ����*isbusy - �ȴ��¶�ת���������ⲿ��ʱ780ms
					*sign - ������ţ����ϻ����£�
          *integer - ������������
          *decimal - ����С������
����ֵ  ����
*******************************************/
void Ds18b20_Read_Temperature(unsigned char *isbusy,
											unsigned char *sign ,
                      unsigned char *interger ,
                      unsigned int *decimal)
{
    unsigned char a=0;
    unsigned char b=0;
    //volatile unsigned char c=0;
    //volatile unsigned char d=0;
    //volatile unsigned char e=0;
    
    unsigned int tmp ;
    
		if(!(*isbusy))
		{
			DS18B20_Init();
			Write_OneByte_ToDS18b20(ROM_Read_Cmd);
  
			DS18B20_Init();
			Write_OneByte_ToDS18b20(ROM_Skip_Cmd);//���������кŲ���
			Write_OneByte_ToDS18b20(Convert_T); //�����¶�ת��
		
			*isbusy=1;
		}
    //DelayMs(780);//�ȴ�DS18b20ת�����
	
    if(*isbusy>78)
		{
			*isbusy=0;
			DS18B20_Init();
			Write_OneByte_ToDS18b20(ROM_Skip_Cmd);
			Write_OneByte_ToDS18b20(Read_Scratchpad); //��ȡ�Ĵ������ݣ����ԴӼĴ���0�����Ĵ���8��
			
			a= Read_OneByte_FromDS18b20();     //�¶ȵ�8λ
			b= Read_OneByte_FromDS18b20();     //�¶ȸ�8λ
			//c= Read_OneByte_FromDS18B20();   //TH
			//d= Read_OneByte_FromDS18B20();   //TL
			//e= Read_OneByte_FromDS18B20();   //Configuration Register
    
			Tx_ResetPulse();  //�ж����ݶ�ȡ
			tmp = (b<<8) | a ;
			if(b & 0xF0)
			{
			*sign = 1 ;              //���Ų���
			tmp = ~tmp+1 ;
			}
			else 
			{
			*sign = 0 ;
			}
			*interger = (tmp>>4) & 0x00FF;  //��������
			*decimal = (tmp & 0x000F) * 625 ; //С������ 
		}
		
}
/******************************************
�������ƣ�Write_EEPROM
��    �ܣ�д���ò���
��    ����Th - �����¶�����
          Tl - �����¶�����
          Register_Con - ���ƼĴ�����ֵ
����ֵ  ������������
*******************************************/
void Write_EEPROM(unsigned char Th,unsigned char Tl,unsigned char Register_Con )
{
  
    DS18B20_Init();
    Write_OneByte_ToDS18b20(ROM_Skip_Cmd);
    Write_OneByte_ToDS18b20(Write_Scratchpad);
    
    Write_OneByte_ToDS18b20(Th);//Th=7F
    Write_OneByte_ToDS18b20(Tl);//Tl=FF ���λ����λ
    Write_OneByte_ToDS18b20(Register_Con);//12λģʽ
    
    delay_ms(700);
    DS18B20_Init();
    Write_OneByte_ToDS18b20(ROM_Skip_Cmd);
    Write_OneByte_ToDS18b20(Copy_Scratchpad);//���Ĵ���������ֵд��EEPROM
    
    delay_ms(300);
 
}
/******************************************
�������ƣ�DS18B20_Init
��    �ܣ���ʼ��DS18b20
��    ������
����ֵ  ����
*******************************************/
void DS18B20_Init(void)
{
    Tx_ResetPulse();
    Rx_PresencePulse(); 
}
