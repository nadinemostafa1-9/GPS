 /******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.c
 *
 * Description: Source file for Os Scheduler.
 *
 ******************************************************************************/

#include "LCD.h"
#include "bluetooth.h"
#include "motors.h"
#include "GPS.h"
#include "GPT.h"
#include "PWM.h"
#include "APP.h"
#include "Os.h"
#include "Ultrasonic.h"
#include "buzzer_LED.h"
#include "EEPROM.h"

/* Global variable store the Os Time */
static uint8 g_Time_Tick_Count = 0;

/* Global variable to indicate the the timer has a new tick */
static uint8 g_New_Time_Tick_Flag = 0;

/*********************************************************************************************/
void Os_start(void)
{
    /* Global Interrupts Enable */
    Enable_Interrupts();
    
    /* 
     * Set the Call Back function to call Os_NewTimerTick
     * this function will be called every SysTick Interrupt (20ms)
     */
    SysTick_SetCallBack(Os_NewTimerTick);

    /* Start SysTickTimer to generate interrupt every 20ms */
    SysTick_Start(OS_BASE_TIME);

    /* Execute the Init Task */
    Init_Task();

    /* Start the Os Scheduler */
    Os_Scheduler();
}

/*********************************************************************************************/
void Os_NewTimerTick(void)
{
    /* Increment the Os time by OS_BASE_TIME */
    g_Time_Tick_Count   += 1;

    /* Set the flag to 1 to indicate that there is a new timer tick */
    g_New_Time_Tick_Flag = 1;
}

/*********************************************************************************************/
void Os_Scheduler(void)
{
    LCD_clearScreen();
    LCD_displayString("Hello"); 
    
    while(1)
    {     
	/* Code is only executed in case there is a new timer tick */
	if(g_New_Time_Tick_Flag == 1)
	{
          g_New_Time_Tick_Flag = 0;
	    switch(g_Time_Tick_Count)
            {
		case 0:
                case 1:
                case 2:
                  bluetooth_checking();
                  update_buzzer();     
                  break;
                  
                case 3:
                  bluetooth_checking();
                  GPS_checking();
                  LCD_update();
                  LED_update();
                  g_Time_Tick_Count = 0;
                  break;
            }          
        }
    } 
}
/*********************************************************************************************/
