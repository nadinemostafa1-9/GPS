/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.h
 *
 * Description: Header file for the PWM driver
 *
 *
 *******************************************************************************/


#ifndef PWM_H_
#define PWM_H_
#endif
   
#include "Platform_Types.h"
#include "tm4c123gh6pm_registers.h"

// selsect a prescale from 0 to 6 {2,4,8,16,32,64}
#define Prescale 2
#define desired_freq 300
#define Mode 0 // 0 for down and 1 for up
#define Freq 16000000

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void PINS_Init();
void PWM_init();
void PWM_SET(uint32 Duty_Cycle);
void PWM_Output_Enable(uint32 PinNum); // 1 for PE4, 2 for PE5, 3 for PD0, 4 for PD1
void PWM_Output_Disable();