 /******************************************************************************
 *
 * Module: bluetooth
 *
 * File Name: bluetooth.c
 *
 * Description: Source file for bluetooth.c
 ******************************************************************************/

#include "bluetooth.h"
#include "Uart.h"

/* Global buffer to hold the bluetooth new message*/
uint8 bluetooth_buff[25] = {0};

/* Global variable to hold the uart module address of bluetooth */
volatile uint32* bluetooth_moduleAddress = (volatile uint32 *)UART1;

/* Global flag to indicate the the bluetooth has a new message */
volatile uint8 bluetooth_NewMessageFlag = 0;

void bluetooth_init()
{   
  /* Calling the UART init function and give to it:
     1- The bluetooth module number.
     2- The bluetooth Port number.
     3- The Rx and Tx pin numbers.
     4- Pointer to be set to the uart module base address. */
    UART_init(BLUETOOTH_UART_MODULE, BLUETOOTH_PORT, BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN, bluetooth_moduleAddress);
    bluetooth_buff[0] = '\0';
}

void bluetooth_receiveByte(void)
{
  static uint8 i=0;
  uint8 c;
  c =  UART_receiveByte(bluetooth_moduleAddress);
  if (c == '.')
  {
    bluetooth_buff[i] = '\0';
    i=0;
    bluetooth_NewMessageFlag = 1;
  }
  else
  {
    bluetooth_buff[i] = c;
    i++;
  }
   
}

void bluetooth_sendByte(uint8 data)
{
   UART_sendByte(data, bluetooth_moduleAddress);
}


void bluetooth_sendString(uint8 *Str)
{
    UART_sendString(Str, bluetooth_moduleAddress);
}