 /******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: Ultrasonic.h
 *
 * Description: Header file for the Ultrasonic driver
 *
 *
 *******************************************************************************/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "Platform_Types.h"
#include "tm4c123gh6pm_registers.h"
#include "Timer0_GPTM.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Pins_Init();
void Ultrasonic_Init();
void Ultrasonic_startTrigger();
uint8 measure_distance();
void Ultrasonic_start();


#endif
