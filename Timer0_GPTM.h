/******************************************************************************
 *
 * Module: GPT
 *
 * File Name: GPT.h
 *
 * Description: header file for the GPT driver
 *
 *
 *******************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_

#include "Platform_Types.h"
#include "tm4c123gh6pm_registers.h"
   
extern int volatile flag;
extern uint32 volatile lastEdge;
extern uint32 volatile thisEdge;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timer0_init(); 
void Timer0_DutyCycle();

#endif

