 /******************************************************************************
 *
 * Module: bluetooth
 *
 * File Name: bluetooth.c
 *
 * Description: Header file for bluetooth.
 ******************************************************************************/

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "tm4c123gh6pm_registers.h"
#include "Platform_Types.h"
   
/* Global flag to indicate the the bluetooth has a new message */
extern volatile uint8 bluetooth_NewMessageFlag;

/* Global buffer to hold the bluetooth new message*/
extern uint8 bluetooth_buff[25];

 /******************************************************************************
 Bluetooth configured Pins
 ******************************************************************************/
#define BLUETOOTH_UART_MODULE          1
#define BLUETOOTH_MODULE_ADDRESS       UART1
#define BLUETOOTH_PORT                 PORTB
#define BLUETOOTH_TX_PIN               1
#define BLUETOOTH_RX_PIN               0

/* Decleration of Bluetooth init function*/
void bluetooth_init();

/* Decleration of Bluetooth send byte function*/
void bluetooth_sendByte(uint8 data);

/* Decleration of Bluetooth send string function*/
void bluetooth_sendString(uint8 *Str);

#endif /* BLUETOOTH_H_ */
