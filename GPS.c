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
#include <math.h>

#define PI 3.14

/* Global variable to hold the uart module base address*/
volatile uint32 * GPS_module = (volatile uint32 *)UART2;

/* Global flag to indicate the the GPS has a new message */
volatile uint8 GPS_NewMessageFlag = 0;

/* Global buffers to hold latitude and longitude */
uint8 latitude[25] = {0};
uint8 longitude[25] = {0};
double previouse_latitude = 0;
double previouse_longitude = 0;

/* buffer to hold the whole "$GPGLL" statement. */
uint8 GPS_buff[50] = {0};

/* buffer to hold the "$GPGLL" string to be cehcked */
static uint8 GPGLL[7] = {0};

uint8 GPS_newDistance =0;

void GPS_init()
{   
  /* Calling the UART init function and give to it:
     1- The GPS module number.
     2- The GPS Port number.
     3- The Rx and Tx pin numbers.
     4- Pointer to be set to the uart module base address. */
    UART_init(GPS_UART_MODULE, GPS_PORT, GPS_TX_PIN, GPS_RX_PIN, GPS_module);
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
    uint8 j = 4;
    uint8 temp_buff[25];
    uint8 comma = 0;
    double temp_fraction;

    /* Checking if the latitude is correct to start parsing */
    if(GPS_buff[0] == '3' && GPS_buff[1] == '0')
    {
        latitude[1] = GPS_buff[0];
        latitude[2] = GPS_buff[1];
        latitude[3] = '.';

        while(1)
        {
          if(GPS_buff[i] == '.')
          {
          }
          else if(GPS_buff[i] == ',')
          {
            comma++;
              if(comma == 2)
              {
                comma = 0;
                i++;
                j++;
                break;
              }
          }

          else if (GPS_buff[i] == 'N')
          { latitude[0] = '+'; }
          else if(GPS_buff[i] == 'S')
          { latitude[0] = '-'; }
          else
          {
            latitude[j] = GPS_buff[i];
            j++;
          }
          i++;
        }
        latitude[j] = '\0';
        while(GPS_buff[i] == '0')
        {
        	i++;
        }
        j=4;
        
        
        longitude[1] = GPS_buff[i];
        longitude[2] = GPS_buff[i+1];
        longitude[3] = '.';
        i+=2;

        while(1)
        {
          if(GPS_buff[i] == '.')
          {
          }
          else if(GPS_buff[i] == ',')
          {
            comma++;
              if(comma == 2)
              {
                comma = 0;
                i++;
                j++;
                break;
              }
          }

          else if (GPS_buff[i] == 'E')
          { longitude[0] = '+'; }
          else if(GPS_buff[i] == 'W')
          { longitude[0] = '-'; }
          else
          {
            longitude[j] = GPS_buff[i];
            j++;
          }
          i++;
        }
        longitude[j] = '\0';


        temp_buff[0] = latitude[4];
        temp_buff[1] = latitude[5];
        temp_buff[2] = '.';
        j=6;
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
        if(latitude[0] == '-')
        {
        	temp_fraction *= -1;
        }
        sprintf(latitude,"%.7f", temp_fraction);


        temp_buff[0] = longitude[4];
        temp_buff[1] = longitude[5];
        temp_buff[2] = '.';
        j=6;
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
        if(longitude[0] == '-')
        {
           temp_fraction *= -1;
        }
        sprintf(longitude,"%.7f", temp_fraction);
        
        new_distance(previouse_latitude, previouse_longitude, atof(latitude), atof(longitude));
        
        if(GPS_newDistance <= 5)
        {
          previouse_latitude = atof(latitude);
          previouse_longitude = atof(longitude);
        }
    }
    else
    {
      latitude[0] = '\0';
      longitude[0] = '\0';
    }
}

double deg2rad(double deg) {
        return (deg * PI / 180.0);
    }

double rad2deg(double rad) {
        return (rad * 180.0 /PI);
    }

void new_distance(double lat1,double lon1,double lat2,double lon2)
{
  if(lat1 != 0 && lon1 != 0)
  {
      double theta = lon1 - lon2;
        double dist = sin(deg2rad(lat1))
                * sin(deg2rad(lat2))
                + cos(deg2rad(lat1))
                * cos(deg2rad(lat2))
                * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
      GPS_newDistance = ceil(1609.344*dist);
  }
}


void GPS_sendCoordinates()
{
  if(latitude[0] != '\0' && longitude[0] != '\0')
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
     latitude[0] = '\0';
     longitude[0] = '\0'; 
  }
}
