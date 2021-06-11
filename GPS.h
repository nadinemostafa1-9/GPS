 /******************************************************************************
 *
 * Module: GPS
 *
 * File Name: GPS.c
 *
 * Description: Header file for GPS.
 ******************************************************************************/

#ifndef GPS_H_
#define GPS_H_

#include "tm4c123gh6pm_registers.h"
#include "Platform_Types.h"

/* Global flag to indicate the the GPS has a new message */
extern volatile uint8 GPS_NewMessageFlag;

/* Global buffers to hold latitude and longitude */   
extern uint8 latitude[25];
extern uint8 longitude[25];

extern double previouse_latitude;
extern double previouse_longitude;

/* buffer to hold the whole "$GPGLL" statement. */
extern uint8 GPS_buff[50];

/* variable to hold the calculated new distance. */
extern uint8 GPS_newDistance;
   
 /******************************************************************************
 GPS configured Pins
 ******************************************************************************/
#define GPS_UART_MODULE          2
#define GPS_PORT                 PORTD
#define GPS_TX_PIN               7
#define GPS_RX_PIN               6

/* Decleration of GPS init function*/
void GPS_init();

void GPS_parsing(void);

void new_distance(double lat1,double lon1,double lat2,double lon2);

void GPS_sendCoordinates();
#endif /* GPS_H_ */
