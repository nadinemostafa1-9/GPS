 /******************************************************************************
 *
 * Module: Application
 *
 * File Name: App.c
 *
 * Description: Source file for Application Tasks.
 *
 ******************************************************************************/

#include "App.h"
#include "LCD.h"
#include "bluetooth.h"
#include "motors.h"
#include "GPS.h"
#include "GPT.h"
#include "PWM.h"
#include "buzzer_LED.h"
#include "Ultrasonic.h"
#include "EEPROM.h"
   
uint8 static systemUnlocked = 0;
uint8 static carMovment = 0;
uint8 static trajectoryMode = 0;  /* 1 for new tour, 2 for last tour */
uint8 static buzzer_flag = 0;
uint32 GPS_TotalDistance = 0;
uint8 stooring_flag = 0;
   
/*buff to store the coordinates*/
int coordinates_array[400];
/* variable to hold the number of int stored in the buff*/
int GPS_i = 1;

/* Description: Task executes once to initialize all the Modules */
void Init_Task(void)
{
    /* Initialize LCD Driver */
    LCD_init();
    
    /* Initialize bluetooth Driver */
    bluetooth_init();
    
    /* Initialize motors Driver  */
    PWM_init();
    
    motor_init();
    
    /* Initialize GPS Driver */
    GPS_init();
    
    /* Initialize buzzer */
    buzzer_init();
    
    /* Initialize LED */
    LED_init();
    
    /*Initialize ultrasonic Driver */
    Ultrasonic_Init();
    
    /*Initialize EEPROM Driver */
    EEPROM_init();
}
