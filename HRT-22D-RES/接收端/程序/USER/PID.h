#ifndef __PID_H
#define __PID_H

#include "include.h"

typedef 
struct
{    
    uint16_t HMI_P;
    uint16_t HMI_I;
    uint16_t HMI_D;
    uint16_t Set;    
    float LastError;
    float PrevError;
    float Error;
    float Real_P;
    float Real_I;
    float Real_D;   
    float Out;
    uint16_t Now;
}PID_s;



#endif
