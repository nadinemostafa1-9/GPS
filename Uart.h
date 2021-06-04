 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: UART.c
 *
 * Description: Header file for UART.
 ******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "tm4c123gh6pm_registers.h"
#include "Platform_Types.h"

/*Decleration of init function*/
void UART_init(uint8 module, uint8 port, uint8 TX, uint8 RX, volatile uint32* current_module);

/* Decleration of the receive byte function */
uint8 UART_receiveByte(volatile uint32 * current_module);

/* Decleration of the send byte function */
void UART_sendByte(uint8 data, volatile uint32 * current_module);

/* Decleration of the send string function */
void UART_sendString(const uint8 *Str, volatile uint32 * current_module);

#endif /* UART_H_ */