#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "GPIO.h" 
#include "EXTI.h" 
#include "oled.h" 
#include "Lora_Moudule.h" 
#include "Timer.h" 
#include "Battery_Voltage.h" 


#define BEEP_Port            GPIOB
#define BEEP_Pin             GPIO_Pin_14
#define STOP_Port            GPIOB
#define STOP_Pin             GPIO_Pin_5
#define GO_Port              GPIOB
#define GO_Pin               GPIO_Pin_4
#define SWITCH_Port          GPIOB
#define SWITCH_Pin           GPIO_Pin_3
#define Lora_M0_Port         GPIOB
#define Lora_M0_Pin          GPIO_Pin_15
#define Lora_M1_Port         GPIOA
#define Lora_M1_Pin          GPIO_Pin_8

extern int first; 
extern int second; 
extern int third; 
extern uint16_t RX_TEXT;

extern int Timenum;
