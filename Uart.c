 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: UART.c
 *
 * Description: Source file for UART.
 ******************************************************************************/

#include "Uart.h"

void UART_init(uint8 module, uint8 port, uint8 TX, uint8 RX, volatile uint32* current_module)
{  
     /* Pointer to the uart port base address */
     volatile uint32 * current_port;
     
     /* point to the current uart port base regisiter */
     switch(port)
     {
         case PORTA:
           current_port = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;      /* PARTA Base Address */
           break;
         case PORTB:
           current_port = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;      /* PARTB Base Address */
           break;
         case PORTC:
           current_port = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;      /* PARTC Base Address */
           break;
         case PORTD:
           current_port = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;      /* PARTD Base Address */
           break;
         case PORTE:
           current_port = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;      /* PARTE Base Address */
           break;
         case PORTF:
           current_port = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;      /* PARTF Base Address */
           break;
     }
      
    /*Enable clock for the UART module for GPS*/
    UART_RCGCUART_REG |= (1<<module);
    /*Enable the clock to the appropriate GPIO module*/
    SYSCTL_REGCGC2_REG |= (1<<port);
    /*Disable UART by clearing  UART, TXE, RXE bits in UARTCTL*/
    *(volatile uint32 *)((volatile uint8 *)current_module + UARTCTL_OFFSET) &=~(0x301);
    /*Writing the values for baud rate in UARTBRD and UARTFBRD
      UART Baud Rate =  ( f / 16 x baud divisor) 
      9600 =  (16MHz / 16 x baud divisor) 
      Baud divisor = 1000000/9600 = 104.1667
      IBRD = 104
      FBRD = 0.166 x 64 + 0.5 = 11*/
    *(volatile uint32 *)((volatile uint8 *)current_module + UARTIBRD_OFFSET) = 104;
    *(volatile uint32 *)((volatile uint8 *)current_module + UARTFBRD_OFFSET) = 11;
    /* Write the desired parameters: 
       Word length = 8 bits,
       no FIFO, 
       Number of stop bits = 1
       Parity disable*/
    *(volatile uint32 *)((volatile uint8 *)current_module + UARTLCRH_OFFSET) = 0x60;
    /*Set GPIO AFSEL*/
    *(volatile uint32 *)((volatile uint8 *)current_port + GPIO_AFSEL_OFFSET) |= (1<<TX) | (1<<RX);
    /*Set GPIO PCTL*/
    *(volatile uint32 *)((volatile uint8 *)current_port + GPIO_PCTL_OFFSET) |= (1<<(TX*4)) | (1<<(RX*4));
    /*Disable analoge*/
    *(volatile uint32 *)((volatile uint8 *)current_port + GPIO_GPIOAMSEL_OFFSET) &= ~((1<<TX) | (1<<RX));
    /*Set GPIO Digital Enable*/
    *(volatile uint32 *)((volatile uint8 *)current_port + GPIO_DEN_OFFSET) |= (1<<TX) | (1<<RX);
    /*Configure the UART clock source by writting to the UARTCC register*/
    *(volatile uint32 *)((volatile uint8 *)current_module + UARTCC_OFFSET) = 0x00;
    /*Enable UART by setting UART, TXE, RXE bits in UARTCTL*/
     *(volatile uint32 *)((volatile uint8 *)current_module + UARTCTL_OFFSET) |= 0x301;
     
     /* enable interrupt */ 
    *(volatile uint32 *)((volatile uint8 *)current_module + UARTICR_OFFSET) &= ~(0x0780);; // Clear receive interrupt
    *(volatile uint32 *)((volatile uint8 *)current_module + UARTIM_OFFSET) = 0x0010;
    
    /* Enable enterrupt of uart module by it's order in vector table */
    switch(module)
    {
          case 0:
            NVIC_EN0_REG |= (1<< 5);
            break;
          case 1:
            NVIC_EN0_REG |= (1<< 6);
            break;
          case 2:
            NVIC_EN1_REG |= (1 << 1);
            break;
          case 3:
            NVIC_EN1_REG |= (1 << 27);
            break;
          case 4:
            NVIC_EN1_REG |= (1 << 28);
            break;
          case 5:
            NVIC_EN1_REG |= (1 << 29);
            break;
          case 6:
            NVIC_EN1_REG |= (1 << 30);
            break;
          case 7:
            NVIC_EN1_REG |= (1 << 31);
            break;      
    }
}


uint8 UART_receiveByte(volatile uint32 * current_module)  
{
    uint8 data;
    (*(volatile uint32 *)((volatile uint8 *)current_module + UARTICR_OFFSET)) &= ~(0x010); // Clear receive interrupt
    data = *(volatile uint32 *)((volatile uint8 *)current_module + UARTDR_OFFSET);
    return data;
}

void UART_sendByte(uint8 data, volatile uint32 * current_module)
{
    /* wait until Tx buffer not full */
    while((*(volatile uint32 *)((volatile uint8 *)current_module + UARTFR_OFFSET) & 0x20) != 0);
    /* before giving it another byte */
    *(volatile uint32 *)((volatile uint8 *)current_module + UARTDR_OFFSET) = data;                  
}

void UART_sendString(const uint8 *Str, volatile uint32 * current_module)
{
        /* iterator to loop through the whole string */
	uint8 i = 0;
        /* Checking if the string doesn't finish */
	while(Str[i] != '\0')
	{
                /* Send the current character */
		UART_sendByte(Str[i], current_module);
		i++;
	}
        /* Send a null terminator caracter to tell that the string is end. */
	UART_sendByte('/', current_module);
}