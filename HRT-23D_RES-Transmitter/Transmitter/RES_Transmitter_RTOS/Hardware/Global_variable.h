#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "GPIO.h" 
#include "EXTI.h" 
#include "oled.h" 
#include "Lora_Moudule.h" 
#include "Timer.h" 
#include "Battery_Voltage.h" 
#include "Task_schedule.h" 
#include "Processes.h" 
#include "oled.h"

#define BEEP_Port            GPIOB
#define BEEP_Pin             GPIO_Pin_14
#define STOP_Port            GPIOB
#define STOP_Pin             GPIO_Pin_5
#define GO_Port              GPIOB
#define GO_Pin               GPIO_Pin_4
#define SWITCH_Port          GPIOB
#define SWITCH_Pin           GPIO_Pin_3
#define Lora_M0_Port         GPIOB
#define Lora_M0_Pin           GPIO_Pin_15
#define Lora_M1_Port         GPIOA
#define Lora_M1_Pin          GPIO_Pin_8
#define Switch_Key_State     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define Stop_Key_State       GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define Go_Key_State         GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define RED_Port             GPIOB
#define RED_Pin              GPIO_Pin_13
#define BLUE_Port            GPIOA
#define BLUE_Pin             GPIO_Pin_6
#define YELLOW_Port          GPIOB
#define YELLOW_Pin           GPIO_Pin_12
#define GREEN_Port           GPIOA
#define GREEN_Pin            GPIO_Pin_5

#define Emergency_Stop       0xA0
#define Ready                0xB0
#define Slow_Stop            0xC0
#define GO                   0xD0

#define RES_Receiver_Emergency_Stop       0xAB
#define RES_Receiver_Ready                0xCC
#define RES_Receiver_Slow_Stop            0x66
#define RES_Receiver_GO                   0x3F

extern uint8_t RES_STATE;
extern int voltage_first; 
extern int voltage_second; 
extern int voltage_third; 
extern uint16_t RES_Receiver_State;
extern int SWITCH_KEY_Flag;
extern int Timenum;
extern uint16_t Offline_count;
extern uint8_t  Offline_Flag;
extern int GO_Key_Flag;
extern int Old_GO_Key_Flag;
extern int GO_Key_Count;
extern int GO_Key_End;
extern uint8_t Old_RES_STATE;
extern float Voltage;
extern int State_Error;
extern uint8_t State_Switch_Count;

