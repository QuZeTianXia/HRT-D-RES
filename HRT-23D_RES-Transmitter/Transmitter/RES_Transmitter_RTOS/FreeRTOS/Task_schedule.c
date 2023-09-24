#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"


//@��ʼ����
//�������ȼ�
#define START_TASK_PRIO		 1
//�����ջ��С	
#define START_STK_SIZE 		32 
//������
TaskHandle_t StartTask_Handler;
//������
void Start_Task(void *pvParameters);
 
 
 //@OLED��ʾ����
//�������ȼ�
#define OLED_TASK_PRIO		 6
//�����ջ��С	
#define OLED_STK_SIZE 		128 
//������
TaskHandle_t OLEDTask_Handler;
//������
void OLED_Task(void *pvParameters);


 //@��ص�ѹ�������
//�������ȼ�
#define Battery_monitor_TASK_PRIO		 2
//�����ջ��С	
#define Battery_monitor_STK_SIZE 		128
//������
TaskHandle_t Battery_monitorTask_Handler;
//������
void Battery_monitor_Task(void *pvParameters);


 //@Lora��������
//�������ȼ�
#define Lora_Send_TASK_PRIO		 10
//�����ջ��С	
#define Lora_Send_STK_SIZE 		128
//������
TaskHandle_t Lora_SendTask_Handler;
//������
void Lora_Send_Task(void *pvParameters);


 //@����״̬�������
//�������ȼ�
#define Connection_Status_Monitor_TASK_PRIO		 10
//�����ջ��С	
#define Connection_Status_Monitor_STK_SIZE 		32 
//������
TaskHandle_t Connection_Status_MonitorTask_Handler;
//������
void Connection_Status_Monitor_Task(void *pvParameters);


 //@GO���������������
//�������ȼ�
#define GO_Key_Schedule_TASK_PRIO		 5
//�����ջ��С	
#define GO_Key_Schedule_STK_SIZE 		64  
//������
TaskHandle_t GO_Key_ScheduleTask_Handler;
//������
void GO_Key_Schedule_Task(void *pvParameters);

 //@״ָ̬ʾ������
//�������ȼ�
#define Indicator_LED_TASK_PRIO		 4
//�����ջ��С	
#define Indicator_LED_STK_SIZE 		64  
//������
TaskHandle_t Indicator_LEDTask_Handler;
//������
void Indicator_LED_Task(void *pvParameters);

 //@����������ָʾ����
//�������ȼ�
#define Indicator_BEEP_TASK_PRIO		 3
//�����ջ��С	
#define Indicator_BEEP_STK_SIZE 		64  
//������
TaskHandle_t Indicator_BEEPTask_Handler;
//������
void Indicator_BEEP_Task(void *pvParameters);

 //@״̬ת������ж�����
//�������ȼ�
#define State_Transition_Judge_TASK_PRIO		9
//�����ջ��С	
#define State_Transition_Judge_STK_SIZE 		64   
//������
TaskHandle_t State_Transition_JudgeTask_Handler;
//������
void State_Transition_Judge_Task(void *pvParameters);


 //@�����ȶ�����
//�������ȼ�
#define Offline_TASK_PRIO		 8
//�����ջ��С	
#define Offline_Task_STK_SIZE   64	    
//������
TaskHandle_t OfflineTask_Handler;
//������
void Offline_Task(void *pvParameters);


 //@ת��״̬�жϲ�������
//�������ȼ�
#define State_Switch_Judgement_Parallel_TASK_PRIO		 8
//�����ջ��С	
#define State_Switch_Judgement_Parallel_Task_STK_SIZE   64	    
//������
TaskHandle_t State_Switch_Judgement_ParallelTask_Handler;
//������
void State_Switch_Judgement_Parallel_Task(void *pvParameters);


//��ʼ����������
void Start_Task(void *pvParameters)
{
    taskENTER_CRITICAL();//�����ٽ���
          					
	 //����OLED����
    xTaskCreate((TaskFunction_t )OLED_Task,     
                (const char*    )"OLED_Task",   
                (uint16_t       )OLED_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )OLED_TASK_PRIO,
                (TaskHandle_t*  )&OLEDTask_Handler);
				
   				
    //������ص�ѹ�������
    xTaskCreate((TaskFunction_t )Battery_monitor_Task,     
                (const char*    )"Battery_monitor_Task",   
                (uint16_t       )Battery_monitor_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Battery_monitor_TASK_PRIO,
                (TaskHandle_t*  )&Battery_monitorTask_Handler);                


	//����Lora��������
    xTaskCreate((TaskFunction_t )Lora_Send_Task,     
                (const char*    )"Lora_Send_Task",   
                (uint16_t       )Lora_Send_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Lora_Send_TASK_PRIO,
                (TaskHandle_t*  )&Lora_SendTask_Handler); 


	//��������״̬�������
    xTaskCreate((TaskFunction_t )Connection_Status_Monitor_Task,     
                (const char*    )"Connection_Status_Monitor_Task",   
                (uint16_t       )Connection_Status_Monitor_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Connection_Status_Monitor_TASK_PRIO,
                (TaskHandle_t*  )&Connection_Status_MonitorTask_Handler); 

				
	//����GO���������������
    xTaskCreate((TaskFunction_t )GO_Key_Schedule_Task,     
                (const char*    )"GO_Key_Schedule_Task",   
                (uint16_t       )GO_Key_Schedule_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )GO_Key_Schedule_TASK_PRIO,
                (TaskHandle_t*  )&GO_Key_ScheduleTask_Handler); 			
	
				
	//����״ָ̬ʾ������
    xTaskCreate((TaskFunction_t )Indicator_LED_Task,     
                (const char*    )"Indicator_LED_Task",   
                (uint16_t       )Indicator_LED_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Indicator_LED_TASK_PRIO,
                (TaskHandle_t*  )&Indicator_LEDTask_Handler); 		

				
	//����״ָ̬ʾ������
    xTaskCreate((TaskFunction_t )Indicator_BEEP_Task,     
                (const char*    )"Indicator_BEEP_Task",   
                (uint16_t       )Indicator_BEEP_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Indicator_BEEP_TASK_PRIO,
                (TaskHandle_t*  )&Indicator_BEEPTask_Handler); 
				
				
	//����״̬ת������ж�����
    xTaskCreate((TaskFunction_t )State_Transition_Judge_Task,     
                (const char*    )"State_Transition_Judge_Task",   
                (uint16_t       )State_Transition_Judge_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )State_Transition_Judge_TASK_PRIO,
                (TaskHandle_t*  )&State_Transition_JudgeTask_Handler); 
				
	//������������
    xTaskCreate((TaskFunction_t )Offline_Task,     
                (const char*    )"Offline_Task",   
                (uint16_t       )Offline_Task_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Offline_TASK_PRIO,
                (TaskHandle_t*  )&OfflineTask_Handler); 


	//����ת��״̬�жϲ�������
    xTaskCreate((TaskFunction_t )State_Switch_Judgement_Parallel_Task,     
                (const char*    )"State_Switch_Judgement_Parallel_Task",   
                (uint16_t       )State_Switch_Judgement_Parallel_Task_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )State_Switch_Judgement_Parallel_TASK_PRIO,
                (TaskHandle_t*  )&State_Switch_Judgement_ParallelTask_Handler); 
				
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
                 
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

void First_Task(void)
{
	  //������ʼ����
  xTaskCreate((TaskFunction_t )Start_Task,            //������
              (const char*    )"Start_Task",          //��������
              (uint16_t       )START_STK_SIZE,        //�����ջ��С
              (void*          )NULL,                  //���ݸ��������Ĳ���
              (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
              (TaskHandle_t*  )&StartTask_Handler);   //������  
              
  vTaskStartScheduler();          //�����������
  
}


