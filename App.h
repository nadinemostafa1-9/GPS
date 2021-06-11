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

#endif /* APP_H_ */
