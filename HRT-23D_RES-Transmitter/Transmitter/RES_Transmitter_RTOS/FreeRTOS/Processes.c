#include "stm32f10x.h"                  // Device header
#include "Global_variable.h"
#include "bmp.h"

//初始化函数
void Hardware_Init(void)
{	
	GPIOS_Init();
	KEY_Init();
//	Timer_Init();
	OLED_Init();
	Battery_Monitor_Init();
	Lora_Init();
	Lora_Normal_Mode();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //禁用JTAG
	
	RED_ON();
	YELLOW_ON();
	BLUE_ON();
	GREEN_ON();
	
	OLED_ShowPicture(0,0,128,32,BMP2,1);//HRT_LOGO
	OLED_Refresh();
	BEEP_ON();
	Delay_ms(500);
	BEEP_OFF();
	Delay_ms(500);
	OLED_Clear();
	OLED_ShowChinese(3,0,0,20,1);//遥
	OLED_ShowChinese(23,0,1,20,1);//控
	OLED_ShowChinese(43,0,2,20,1);//急
	OLED_ShowChinese(63,0,3,20,1);//停
	OLED_ShowChinese(83,0,4,20,1);//系
	OLED_ShowChinese(103,0,5,20,1);//统
	OLED_ShowString(80,55,"By QZTX",8,1);
	OLED_Refresh();
	BEEP_ON();
	Delay_ms(500);
	BEEP_OFF();
	Delay_ms(500);
	OLED_Clear();
	OLED_ShowChinese(0,0,0,12,1);//已
	OLED_ShowChinese(12,0,1,12,1);//连
	OLED_ShowChinese(24,0,2,12,1);//接
	OLED_ShowChinese(50,0,3,12,1);//电
	OLED_ShowChinese(62,0,4,12,1);//池
	OLED_ShowChinese(74,0,3,12,1);//电
	OLED_ShowChinese(86,0,5,12,1);//压
	OLED_ShowNum(99,0,voltage_third,1,12,1);
	OLED_ShowChar(105,0,'.',12,1);
	OLED_ShowNum(108,0,voltage_second,1,12,1);
	OLED_ShowNum(114,0,voltage_first,1,12,1);
	OLED_ShowChar(120,0,'V',12,1);
	OLED_Refresh();
//	RED_OFF();
//	YELLOW_OFF();
//	BLUE_OFF();
//	GREEN_OFF();
}


//OLED显示任务函数
void OLED_Task(void *pvParameters)
{
    while(1)
    {
        OLED_ShowNum(0,16,RES_Receiver_State,3,16,1);
		OLED_ShowNum(60,16,GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4),3,16,1);
		if(RES_STATE == Emergency_Stop)  OLED_ShowChar(90,16,'E',16,1);
		if(RES_STATE == Ready)  OLED_ShowChar(90,16,'R',16,1);
		if(RES_STATE == Slow_Stop)  OLED_ShowChar(90,16,'S',16,1);
		if(RES_STATE == GO)  OLED_ShowChar(90,16,'G',16,1);
		
		OLED_ShowNum(110,16,GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11),1,16,1);
		
		OLED_Refresh();	
		vTaskDelay(200);
    }
}   
 


//电池电压检测任务函数
void Battery_monitor_Task(void *pvParameters)
{
    while(1)
    {
		Battery_Voltage();
		OLED_ShowNum(99,0,voltage_third,1,12,1);
		OLED_ShowNum(108,0,voltage_second,1,12,1);
		OLED_ShowNum(114,0,voltage_first,1,12,1);

		vTaskDelay(1000);
    }
}

//Lora串口发送任务函数
void Lora_Send_Task(void *pvParameters)
{
    while(1)
    {		
		Lora_SendByte(RES_STATE);
		vTaskDelay(100);
		
    }
}

//连接状态监测任务函数
void Connection_Status_Monitor_Task(void *pvParameters)
{
    while(1)		
    {
		if(Offline_Flag) RES_STATE = Emergency_Stop ;
								
        if(Offline_count == 0)
		{			
			OLED_ShowChinese(0,0,6,12,1);//未
			Offline_Flag = 1;
		}
		else 
		{
			if(Offline_count > 100)
			{				
				OLED_ShowChinese(0,0,6,12,1);//未
				Offline_Flag = 1;
			}
			else  
			{
				OLED_ShowChinese(0,0,0,12,1);//已
				Offline_Flag = 0;
			}
			Offline_count++;
		}
		
						
        vTaskDelay(10);
		
    }    
}

//GO按键任务调度函数
void GO_Key_Schedule_Task(void *pvParameters)
{
    while(1)
    {
		if(!Offline_Flag && RES_STATE == Ready && GO_Key_Flag && !Old_GO_Key_Flag && GO_Key_End == 0)
		{
			GO_Key_Count++;
		}
		if(!Offline_Flag && RES_STATE == Slow_Stop && GO_Key_Flag && !Old_GO_Key_Flag && GO_Key_End == 0 && GO_Exit_Flag)
		{
			GO_Key_Count++;
		}		
		if(!Offline_Flag && RES_STATE == GO && GO_Key_Flag && !Old_GO_Key_Flag && GO_Key_End == 1)
		{
			Old_RES_STATE = RES_STATE ;
			RES_STATE = Slow_Stop ;
			State_Switch_Count = 1;
			State_Error = 0;
			GO_Exit_Flag = 0;
		}
		if(GO_Key_Count >= 30) 
		{
			BEEP_ON();
			vTaskDelay(100);
			BEEP_OFF();
			vTaskDelay(50);
			BEEP_ON();
			vTaskDelay(100);
			BEEP_OFF();
			vTaskDelay(50);
			BEEP_ON();
			vTaskDelay(100);
			BEEP_OFF();
			vTaskDelay(50);
			Old_RES_STATE = RES_STATE ;
			RES_STATE = GO;
			GO_Key_Count = 0;
			State_Switch_Count = 1;
			State_Error = 0;
		}
		if(Old_GO_Key_Flag && !GO_Key_Flag)
		{
			GO_Key_Count = 0;
			GO_Key_End = 1;
		}
		if(!Old_GO_Key_Flag && GO_Key_Flag)
		{
			GO_Key_End = 0;
		}
		
		vTaskDelay(50);
		
    }
}

//状态指示灯任务函数
void Indicator_LED_Task(void *pvParameters)
{
    while(1)		
    {
		if(RES_STATE == Emergency_Stop) 
		{
			RED_ON();
		}
 		else 
		{
			if(RES_STATE == Slow_Stop)
			{
				RED_ON();
			    BLUE_ON();			
			}
			else
			{
				RED_OFF();	
			    BLUE_OFF();
			}
			RED_OFF();
		}
		
		if(RES_STATE == Ready) BLUE_ON();
		else BLUE_OFF();
		
        if(RES_STATE == GO) GREEN_ON();
		else GREEN_OFF();
		
		
		if(Offline_Flag == 1) YELLOW_OFF();
		else YELLOW_ON();
		
        vTaskDelay(30);
		
    }    
}



//蜂鸣器电量指示任务函数
void Indicator_BEEP_Task(void *pvParameters)
{
	vTaskDelay(1000);
    while(1)		
    {
		if((int)(Voltage*100) < 740)
		{
			BEEP_ON();
			vTaskDelay(300);
			BEEP_OFF();
			vTaskDelay(500);
		}
		
    }    
}


//状态转换结果判断任务函数
void State_Transition_Judge_Task(void *pvParameters)
{
    while(1)		
    {
		if(State_Switch_Count < 100 && State_Switch_Count > 0)
		{
			if(RES_STATE == Emergency_Stop )
			{
			}
			else
			{
				if(RES_STATE == Ready) 
				{
					if(RES_Receiver_State != RES_Receiver_Ready)  State_Error++;
				}
				if(RES_STATE == GO) 
				{
					if(RES_Receiver_State != RES_Receiver_GO)  State_Error++;
				}
				if(RES_STATE == Slow_Stop) 
				{
					if(RES_Receiver_State != RES_Receiver_Slow_Stop)  State_Error++;
				}
			}
			if(State_Error > 3)
			{
				RES_STATE = Old_RES_STATE ;
				State_Error = 0;
				State_Switch_Count = 0;				
			}
		}
		
		vTaskDelay(200);
		
   }    
}


//掉线稳定任务函数
void Offline_Task(void *pvParameters)
{
    while(1)		
    {
		if(Offline_Flag)
		{
			Lora_SendByte(Emergency_Stop);
			vTaskDelay(25);
		}
						
    }    
}


//转换判断并行任务函数
void State_Switch_Judgement_Parallel_Task(void *pvParameters)
{
    while(1)		
    {
		if(State_Switch_Count > 0)
		{
			State_Switch_Count++;
		}
		if(State_Switch_Count >= 100)
		{
			State_Switch_Count = 0;
			State_Error = 0;
		}		
		vTaskDelay(10);
    }    
}

