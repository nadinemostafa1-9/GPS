/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: Header file for the LCD driver
 *
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_
#include "Platform_Types.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */

#define DATA_BITS_MODE 4

#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

//#undef UPPER_PORT_PINS

/* LCD HW PINS */

#define LCD_DATA_PORT GPIO_PORTA_BASE_ADDRESS
#define Data_Port_Num 0 // for clock activation
#if (DATA_BITS_MODE == 8)
#define LCD_DATA_REG (*((volatile unsigned long *)(LCD_DATA_PORT + 0x3FC)))
#elif (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
#define LCD_DATA_REG (*((volatile unsigned long *)(LCD_DATA_PORT + 0x3FC)))
#else 
#define LCD_DATA_REG (*((volatile unsigned long *)(LCD_DATA_PORT + 0x3FC)))
#endif
#endif

#define Rs 4 // pin 4 in portB
#define RW 5 // pin 5 in portB
#define E 6 // pin 6 in portB
#define LCD_CTRL_PORT GPIO_PORTB_BASE_ADDRESS
#define LCD_CTRL_DATA (*((volatile unsigned long *)(LCD_CTRL_PORT +0x3FC)))
#define Ctrl_Port_Num 1 // for Clock activation 

/* LCD Commands */

#define CLEAR_COMMAND 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_FOUR_BIT_MODE 0x28
#define CURSOR_OFF 0x0C
#define SET_CURSOR_LOCATION 0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Ctrl_Init();
void Port_Init();
void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char * str);
void LCD_goToRowColumn(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_integertostring(int data);
void LCD_clearScreen();

#endif /* LCD_H_ */
