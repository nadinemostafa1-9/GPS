 /******************************************************************************
 *
 * Module: GPS
 *
 * File Name: GPS.c
 *
 * Description: Source file for GPS.
 ******************************************************************************/

#include "GPS.h"
#include "Uart.h"
#include <stdlib.h>

/* Global variable to hold the uart module base address*/
volatile uint32 * GPS_module = (volatile uint32 *)UART2;

/* Global flag to indicate the the GPS has a new message */
volatile uint8 GPS_NewMessageFlag = 0;

/* Global buffers to hold latitude and longitude */
uint8 latitude[25] = {0};
uint8 longitude[25] = {0};

/* buffer to hold the whole "$GPGLL" statement. */
uint8 GPS_buff[50] = {0};

/* buffer to hold the "$GPGLL" string to be cehcked */
static uint8 GPGLL[7] = {0};

void GPS_init()
{   
  /* Calling the UART init function and give to it:
     1- The GPS module number.
     2- The GPS Port number.
     3- The Rx and Tx pin numbers.
     4- Pointer to be set to the uart module base address. */
    UART_init(GPS_UART_MODULE, GPS_PORT, GPS_TX_PIN, GPS_RX_PIN, GPS_module);
    GPS_buff[0] = '\0';
    GPGLL[0] = '\0';
    latitude[0] = '\0';
    longitude[0] = '\0';
}

void GPS_receive()
{
  static uint8 i=0; /* iterator for GPGLL */
  static uint8 j=0; /* iterator for the whole statment */
  
  uint8 c;
  c =  UART_receiveByte(GPS_module);
  
  /* Check if there is a new line */
  if(c == '$')
  {
    /* j>0 means that the last statment was the GPGLL statment. */
    if(j > 0)  
    {
      /* End the buffer of the last statment by the null terminator */
      GPS_buff[j] = '\0';
      /* Set the new message flag */
      GPS_NewMessageFlag = 1;
    }
    /* Clear both iterators to start a new line buffering */
    j=0;
    i=0;
  }
  
  /* IF GPGLL buffer isn't full */
  if (i<7)
  {
    /* Filing with the GPG characters */
    GPGLL[i] = c;
    i++ ;
  }
  /* IF GPGLL buffer is full */
  else if(i == 7)
  {
    /* Checking for the "$GPGLL," statment */
    if(GPGLL[0] == '$' && GPGLL[1] == 'G' && GPGLL[2] == 'P' && GPGLL[3] == 'G' && GPGLL[4] == 'L' && GPGLL[5] == 'L' && GPGLL[6] == ',')
    {
      /* Filling the statment buffer by the whole line characters. */
      GPS_buff[j] = c;
      GPS_buff[j+1] = '\0';
      j++;
    }
  }
}

/* Function to extract the latitude and longitude from the string */
void GPS_parsing(void)
{
    uint8 i = 2;
    uint8 j = 3;
    uint8 temp_buff[25];
    double temp_fraction;

    /* Checking if the latitude is correct to start parsing */
    if(GPS_buff[0] == '3' && GPS_buff[1] == '0')
    {
        latitude[0] = GPS_buff[0];
        latitude[1] = GPS_buff[1];
        latitude[2] = '.';

        while(GPS_buff[i] != '\0')
        {
          if(GPS_buff[i] == '.')
          {
          }
          else if(GPS_buff[i] == ',')
          {
            i++;
            j++;
            break;
          }

          else if (GPS_buff[i] == 'N')
          {}
          else if(GPS_buff[i] == 'S')
          {}
          else
          {
            latitude[j] = GPS_buff[i];
            j++;
          }
          i++;
        }
        latitude[j] = '\0';

        i+=2;


        while(GPS_buff[i] == '0')
        {
          i++;
        }

        j = 3;
        longitude[0] = GPS_buff[i];
        longitude[1] = GPS_buff[i+1];
        longitude[2] = '.';
        i+=2;
        while(GPS_buff[i] != '\0')
        {
          if(GPS_buff[i] == '.')
          {
          }
          else if(GPS_buff[i] == ',')
          {
            i++;
            j++;
            break;
          }

          else if (GPS_buff[i] == 'N')
          {}
          else if(GPS_buff[i] == 'S')
          {}
          else
          {
            longitude[j] = GPS_buff[i];
            j++;
          }
          i++;
        }
        longitude[j] = '\0';


        temp_buff[0] = latitude[3];
        temp_buff[1] = latitude[4];
        temp_buff[2] = '.';
        j=5;
        i=3;
        while(latitude[j] != '\0')
        {
          temp_buff[i] = latitude[j];
          i++;
          j++;
        }
        temp_buff[i] = '\0';


        temp_fraction = atof(temp_buff);
        temp_fraction /= 60;
        temp_fraction += 30;
        sprintf(latitude,"%.7f", temp_fraction);


        temp_buff[0] = longitude[3];
        temp_buff[1] = longitude[4];
        temp_buff[2] = '.';
        j=5;
        i=3;
        while(longitude[j] != '\0')
        {
          temp_buff[i] = longitude[j];
          i++;
          j++;
        }
        temp_buff[i] = '\0';
        temp_fraction = atof(temp_buff);
        temp_fraction /= 60;
        temp_fraction += 31;
        sprintf(longitude,"%.7f", temp_fraction);
    }
    else
    {
      latitude[0] = '\0';
      longitude[0] = '\0';
    }
}


void GPS_sendCoordinates()
{
    uint8 i=0;
    while(latitude[i] != '\0')
    {
      bluetooth_sendByte(latitude[i]);
      i++;
    }
    bluetooth_sendByte(' ');
    i=0;
    while(longitude[i] != '\0')
    {
      bluetooth_sendByte(longitude[i]);
      i++;
    }
    bluetooth_sendByte('/');
    
}