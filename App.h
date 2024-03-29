 /******************************************************************************
 *
 * Module: application
 *
 * File Name: App.h
 *
 * Description: Header file for Application Tasks.
 *
 ******************************************************************************/

#ifndef APP_H_
#define APP_H_

#include "tm4c123gh6pm_registers.h"
#include "Platform_Types.h"

extern uint32 GPS_distance;

/* Description: Task executes once to initialize all the Modules */
void Init_Task(void);

void bluetooth_checking(void);

void GPS_checking();

void LCD_update();

void update_buzzer();

void LED_update();

#endif /* APP_H_ */
