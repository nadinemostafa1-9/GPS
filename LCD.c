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

void Ctrl_Init()
{
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= (1<<Ctrl_Port_Num);
    delay = SYSCTL_REGCGC2_REG;
    
    *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT + 0x528) &= ~((1<<Rs)|(1<<RW)|(1<<E));          /* Disable Analog on Rs, RW, and E */
    *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT + 0x52C) &=~((0xF<<Rs*4)|(0xF<<RW*4)|(0xF<<E*4));    /* Clear PMCx bits for Rs, RW, and E  */
    *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT + 0x400) |= ((1<<Rs)|(1<<RW)|(1<<E));      /* Configure pins as output pins */
    *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT + 0x420)  &= ~((1<<Rs)|(1<<RW)|(1<<E));          /* Disable alternative function on Rs, RW, and E*/
    *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT + 0x51C) |= ((1<<Rs)|(1<<RW)|(1<<E));          /* Enable Digital I/O on Rs, RW, and E */
    
}

//Initiation of Port that will transfer data between the uc and th LCD 

void Port_Init()
{
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= (1<<Data_Port_Num);
    delay = SYSCTL_REGCGC2_REG;
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x528)))  &= 0x0F;          /* Disable Analog on The Upper Port pins */
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x52C)))  &= 0x0000FFFF;    /* Clear PMCx bits for The Upper Port pins */
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x400)))  = 0xF0;      /* Configure The Upper Port pins as output pins */
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x420)))  &= 0x0F;          /* Disable alternative function on The Upper Port pins*/
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x51C)))  |= 0xF0;          /* Enable Digital I/O on The Upper Port pins */
#else
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x528)))  &= 0xF0;          /* Disable Analog on The Lower Port pins */
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x52C)))  &= 0xFFFF0000;    /* Clear PMCx bits for The Lower Port pins */
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x400)))  = 0x0F;      /* Configure The Lower Port pins as output pins */
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x420)))  &= 0xF0;          /* Disable alternative function on The Lower Port pins*/
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x51C)))  |= 0x0F;          /* Enable Digital I/O on The Lower Port pins */
#endif
#elif (DATA_BITS_MODE == 8)
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x528)))  &= 0x00;          /* Disable Analog on The whole port */
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x52C)))  &= 0x00000000;    /* Clear PMCx bits for The whole port */
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x400)))  = 0xFF;      /* Configure The whole port as output pins */
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x420)))  &= 0x00;          /* Disable alternative function on The whole port*/
    (*((volatile unsigned long *)(LCD_DATA_PORT + 0x51C)))  |= 0xFF;          /* Enable Digital I/O on The whole port */
#endif
}

void LCD_init()
{
	Ctrl_Init();
        Port_Init();
	#if (DATA_BITS_MODE == 4)
	LCD_sendCommand(FOUR_BITS_DATA_MODE);
	LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);
	#elif (DATA_BITS_MODE==8)
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* 2 lines + 8bit mode */
	#endif
	LCD_sendCommand(CURSOR_OFF); /* Cursor_OFF */
	LCD_sendCommand(CLEAR_COMMAND); /* Clear screen */
}
