#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"


//@开始任务
//任务优先级
#define START_TASK_PRIO		 1
//任务堆栈大小	
#define START_STK_SIZE 		32 
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void Start_Task(void *pvParameters);
 
 
 //@OLED显示任务
//任务优先级
#define OLED_TASK_PRIO		 6
//任务堆栈大小	
#define OLED_STK_SIZE 		128 
//任务句柄
TaskHandle_t OLEDTask_Handler;
//任务函数
void OLED_Task(void *pvParameters);


 //@电池电压监测任务
//任务优先级
#define Battery_monitor_TASK_PRIO		 2
//任务堆栈大小	
#define Battery_monitor_STK_SIZE 		128
//任务句柄
TaskHandle_t Battery_monitorTask_Handler;
//任务函数
void Battery_monitor_Task(void *pvParameters);


 //@Lora发送任务
//任务优先级
#define Lora_Send_TASK_PRIO		 10
//任务堆栈大小	
#define Lora_Send_STK_SIZE 		128
//任务句柄
TaskHandle_t Lora_SendTask_Handler;
//任务函数
void Lora_Send_Task(void *pvParameters);


 //@连接状态监测任务
//任务优先级
#define Connection_Status_Monitor_TASK_PRIO		 10
//任务堆栈大小	
#define Connection_Status_Monitor_STK_SIZE 		32 
//任务句柄
TaskHandle_t Connection_Status_MonitorTask_Handler;
//任务函数
void Connection_Status_Monitor_Task(void *pvParameters);


 //@GO按键任务调度任务
//任务优先级
#define GO_Key_Schedule_TASK_PRIO		 5
//任务堆栈大小	
#define GO_Key_Schedule_STK_SIZE 		64  
//任务句柄
TaskHandle_t GO_Key_ScheduleTask_Handler;
//任务函数
void GO_Key_Schedule_Task(void *pvParameters);

 //@状态指示灯任务
//任务优先级
#define Indicator_LED_TASK_PRIO		 4
//任务堆栈大小	
#define Indicator_LED_STK_SIZE 		64  
//任务句柄
TaskHandle_t Indicator_LEDTask_Handler;
//任务函数
void Indicator_LED_Task(void *pvParameters);

 //@蜂鸣器电量指示任务
//任务优先级
#define Indicator_BEEP_TASK_PRIO		 3
//任务堆栈大小	
#define Indicator_BEEP_STK_SIZE 		64  
//任务句柄
TaskHandle_t Indicator_BEEPTask_Handler;
//任务函数
void Indicator_BEEP_Task(void *pvParameters);

 //@状态转换结果判断任务
//任务优先级
#define State_Transition_Judge_TASK_PRIO		9
//任务堆栈大小	
#define State_Transition_Judge_STK_SIZE 		64   
//任务句柄
TaskHandle_t State_Transition_JudgeTask_Handler;
//任务函数
void State_Transition_Judge_Task(void *pvParameters);


 //@掉线稳定任务
//任务优先级
#define Offline_TASK_PRIO		 8
//任务堆栈大小	
#define Offline_Task_STK_SIZE   64	    
//任务句柄
TaskHandle_t OfflineTask_Handler;
//任务函数
void Offline_Task(void *pvParameters);


 //@转换状态判断并行任务
//任务优先级
#define State_Switch_Judgement_Parallel_TASK_PRIO		 8
//任务堆栈大小	
#define State_Switch_Judgement_Parallel_Task_STK_SIZE   64	    
//任务句柄
TaskHandle_t State_Switch_Judgement_ParallelTask_Handler;
//任务函数
void State_Switch_Judgement_Parallel_Task(void *pvParameters);


//开始任务任务函数
void Start_Task(void *pvParameters)
{
    taskENTER_CRITICAL();//进入临界区
          					
	 //创建OLED任务
    xTaskCreate((TaskFunction_t )OLED_Task,     
                (const char*    )"OLED_Task",   
                (uint16_t       )OLED_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )OLED_TASK_PRIO,
                (TaskHandle_t*  )&OLEDTask_Handler);
				
   				
    //创建电池电压监测任务
    xTaskCreate((TaskFunction_t )Battery_monitor_Task,     
                (const char*    )"Battery_monitor_Task",   
                (uint16_t       )Battery_monitor_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Battery_monitor_TASK_PRIO,
                (TaskHandle_t*  )&Battery_monitorTask_Handler);                


	//创建Lora发送任务
    xTaskCreate((TaskFunction_t )Lora_Send_Task,     
                (const char*    )"Lora_Send_Task",   
                (uint16_t       )Lora_Send_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Lora_Send_TASK_PRIO,
                (TaskHandle_t*  )&Lora_SendTask_Handler); 


	//创建连接状态监测任务
    xTaskCreate((TaskFunction_t )Connection_Status_Monitor_Task,     
                (const char*    )"Connection_Status_Monitor_Task",   
                (uint16_t       )Connection_Status_Monitor_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Connection_Status_Monitor_TASK_PRIO,
                (TaskHandle_t*  )&Connection_Status_MonitorTask_Handler); 

				
	//创建GO按键任务调度任务
    xTaskCreate((TaskFunction_t )GO_Key_Schedule_Task,     
                (const char*    )"GO_Key_Schedule_Task",   
                (uint16_t       )GO_Key_Schedule_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )GO_Key_Schedule_TASK_PRIO,
                (TaskHandle_t*  )&GO_Key_ScheduleTask_Handler); 			
	
				
	//创建状态指示灯任务
    xTaskCreate((TaskFunction_t )Indicator_LED_Task,     
                (const char*    )"Indicator_LED_Task",   
                (uint16_t       )Indicator_LED_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Indicator_LED_TASK_PRIO,
                (TaskHandle_t*  )&Indicator_LEDTask_Handler); 		

				
	//创建状态指示灯任务
    xTaskCreate((TaskFunction_t )Indicator_BEEP_Task,     
                (const char*    )"Indicator_BEEP_Task",   
                (uint16_t       )Indicator_BEEP_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Indicator_BEEP_TASK_PRIO,
                (TaskHandle_t*  )&Indicator_BEEPTask_Handler); 
				
				
	//创建状态转换结果判断任务
    xTaskCreate((TaskFunction_t )State_Transition_Judge_Task,     
                (const char*    )"State_Transition_Judge_Task",   
                (uint16_t       )State_Transition_Judge_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )State_Transition_Judge_TASK_PRIO,
                (TaskHandle_t*  )&State_Transition_JudgeTask_Handler); 
				
	//创建掉线任务
    xTaskCreate((TaskFunction_t )Offline_Task,     
                (const char*    )"Offline_Task",   
                (uint16_t       )Offline_Task_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Offline_TASK_PRIO,
                (TaskHandle_t*  )&OfflineTask_Handler); 


	//创建转换状态判断并行任务
    xTaskCreate((TaskFunction_t )State_Switch_Judgement_Parallel_Task,     
                (const char*    )"State_Switch_Judgement_Parallel_Task",   
                (uint16_t       )State_Switch_Judgement_Parallel_Task_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )State_Switch_Judgement_Parallel_TASK_PRIO,
                (TaskHandle_t*  )&State_Switch_Judgement_ParallelTask_Handler); 
				
    vTaskDelete(StartTask_Handler); //删除开始任务
                 
    taskEXIT_CRITICAL();            //退出临界区
}

void First_Task(void)
{
	  //创建开始任务
  xTaskCreate((TaskFunction_t )Start_Task,            //任务函数
              (const char*    )"Start_Task",          //任务名称
              (uint16_t       )START_STK_SIZE,        //任务堆栈大小
              (void*          )NULL,                  //传递给任务函数的参数
              (UBaseType_t    )START_TASK_PRIO,       //任务优先级
              (TaskHandle_t*  )&StartTask_Handler);   //任务句柄  
              
  vTaskStartScheduler();          //开启任务调度
  
}


