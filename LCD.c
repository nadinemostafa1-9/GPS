/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: Source file for the LCD driver
 *
 *
 *******************************************************************************/

#include "tm4c123gh6pm_registers.h"
#include "Platform_Types.h"
#include <stdlib.h>
#include "LCD.h"

//Initiation of the Control pins of the LCD 

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762

void Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}

