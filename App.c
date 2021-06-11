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

void bluetooth_checking()
{
    if(bluetooth_NewMessageFlag == 1)
  {    
    bluetooth_NewMessageFlag = 0;
    
    if(bluetooth_buff[0] == 'n')
    {
        trajectoryMode = 1;
    }
    else if(bluetooth_buff[0] == '@')
    {
        trajectoryMode = 2;
    }
    else if(bluetooth_buff[0] == 'e' && bluetooth_buff[1] == 'm' && bluetooth_buff[2] == 'b' && bluetooth_buff[3] == 'e' 
            && bluetooth_buff[4] == 'd' && bluetooth_buff[5] == 'd' && bluetooth_buff[6] == 'e' && bluetooth_buff[7] == 'd' && systemUnlocked == 0)
    {
      bluetooth_sendByte('y');
      buzzer_flag = 0;
      systemUnlocked = 1;
    }
    else if(bluetooth_buff[0] == 'u')
    {
      if(carMovment == 0)
      {
          move_forward();
          carMovment = 1;
      }
      else
      {
         stop_car();
         carMovment = 0;
      }
    }
    else if(bluetooth_buff[0] == 'd')
    {
      if(carMovment == 0)
      {
          move_backward();
          carMovment = 1;
      }
      else
      {
         stop_car();
         carMovment = 0;
      }
    }
    else if(bluetooth_buff[0] == 'l')
    {
      if(carMovment == 0)
      {
          move_left();
          carMovment = 1;
      }
      else
      {
         stop_car();
         carMovment = 0;
      }
    }
    else if(bluetooth_buff[0] == 'r')
    {
      if(carMovment == 0)
      {
          move_right();
          carMovment = 1;
      }
      else
      {
         stop_car();
         carMovment = 0;
      }
    }
    else if(bluetooth_buff[0] == 's')
    {
         stop_car();
         carMovment = 0;
    }
    else if(systemUnlocked == 1)
    {
        Disable_Interrupts();
        uint8 temp = atoi(bluetooth_buff);
        Enable_Interrupts();
        change_speed(temp);
    }
    else 
    {
      buzzer_flag = 1;
    }
    bluetooth_buff[0] = '\0';
  }
}

void GPS_checking()
{
  /* car isn't stopped, gps new message, system is unlocked, new trajectory mode */
  if(carMovment == 1 && GPS_NewMessageFlag == 1 && systemUnlocked == 1 && trajectoryMode == 1)
  {
      GPS_NewMessageFlag = 0;
      GPS_parsing();
      if(GPS_newDistance <= 5)
      {
         if(latitude[0] == '3' && longitude[0] == '3')
        {
            GPS_sendCoordinates();
            GPS_sendCoordinates();
            GPS_sendCoordinates();
            
            GPS_TotalDistance += GPS_newDistance;
            GPS_newDistance = 0;
            
            if(stooring_flag == 0)
            {
              double lat = atof(latitude);
              int x = lat * 10000000;
              coordinates_array[GPS_i] = x;
              GPS_i++;
               
              lat = atof(longitude);
              x = lat * 10000000;
              coordinates_array[GPS_i] = x;
              GPS_i++;

              coordinates_array[0] = GPS_i;
              if (GPS_TotalDistance >= 100)
              {
                stooring_flag == 1;
                EEPROM_write(coordinates_array, coordinates_array[0]);
              }
            }
        }
      }
  }
  else if(systemUnlocked == 1 && trajectoryMode == 2)
  {
      int j;
      EEPROM_read(&j, 1);
      LCD_integertostring(j);
      Delay_MS(1000);
      EEPROM_read(coordinates_array, j);
      
      for(uint8 i=1; i<j; i++)
      {
        int k = 0;
        uint8 arr[15];
        sprintf(arr, "%.0f", coordinates_array[i]);
        if(arr[0] == '-')
        {
          bluetooth_sendByte(arr[0]);
          bluetooth_sendByte(arr[1]);
          bluetooth_sendByte(arr[2]);
          bluetooth_sendByte('.');
          k=3;
        }
        else
        {
          bluetooth_sendByte(arr[0]);
          bluetooth_sendByte(arr[1]);
          bluetooth_sendByte('.');
          k=2;
        }
        while(arr[k] != '\0')
        {
          bluetooth_sendByte(arr[k]);
        }
        if(i%2 == 1)
          bluetooth_sendByte(' ');
        else
           bluetooth_sendByte('/');
      }
      trajectoryMode = 0;
  }
}

void LCD_update()
{
  if(systemUnlocked == 1)
  {
    if(trajectoryMode == 1)
    {
      LCD_clearScreen();
      LCD_displayString("Distance: ");
      LCD_integertostring(GPS_TotalDistance);
      LCD_displayCharacter('m');
    }
    else if(trajectoryMode == 2)
    {
      LCD_clearScreen();
      LCD_displayString("Sending last");
      LCD_goToRowColumn(1,0);
      LCD_displayString("tour");
    }
  }
}

void update_buzzer()
{
    if(buzzer_flag == 1 || GPS_TotalDistance >= 100)
        buzzer_on();
    else
        buzzer_off();        
}

void LED_update()
{
  if(GPS_TotalDistance >= 100)
    LED_on();
  else
    LED_off();
}
