#include "tm4c123gh6pm_registers.h"
#include <stdlib.h>
#include <math.h>
#include "LCD.h"

/* defines for bluetooth module */
#define BLUETOOTH_UART_MODULE          1
#define BLUETOOTH_MODULE_ADDRESS       UART1
#define BLUETOOTH_PORT                 PORTB
#define BLUETOOTH_TX_PIN               1
#define BLUETOOTH_RX_PIN               0

/* defines for GPS module */
#define GPS_UART_MODULE          2
#define GPS_PORT                 PORTD
#define GPS_TX_PIN               7
#define GPS_RX_PIN               6

/* Initialization of uart interfacing module */
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

/* Initialization of bluetooth module */
void bluetooth_init()
{   
  /* Calling the UART init function and give to it:
     1- The bluetooth module number.
     2- The bluetooth Port number.
     3- The Rx and Tx pin numbers.
     4- Pointer to be set to the uart module base address. */
    UART_init(BLUETOOTH_UART_MODULE, BLUETOOTH_PORT, BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN, bluetooth_moduleAddress);
}

/* Initialization of GPS module */
void GPS_init()
{   
  /* Calling the UART init function and give to it:
     1- The GPS module number.
     2- The GPS Port number.
     3- The Rx and Tx pin numbers.
     4- Pointer to be set to the uart module base address. */
    UART_init(GPS_UART_MODULE, GPS_PORT, GPS_TX_PIN, GPS_RX_PIN, GPS_module);
}

/* Initialization for PWM */
void PWM_init()
{
  // setting the clock of the PWM bit 0 activate the clock of module 0
  SYSCTL_RCGCPWM_REG |= 1;
  volatile unsigned long delay = 0;
  delay = SYSCTL_PRPWM_REG;
  
    //setting pins for PE4 and PE5 pins
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= (1<<4);
  delay = SYSCTL_REGCGC2_REG;
  //setting registers of PE4 and PE5 pins
  GPIO_PORTE_AMSEL_REG = 0;
  GPIO_PORTE_PCTL_REG &= 0xFF00FFFF;
  GPIO_PORTE_DIR_REG |= 0x30;
  GPIO_PORTE_AFSEL_REG |= 0x30;
  GPIO_PORTE_PCTL_REG |= 0x00440000; //M0PWM4 and M0PWM5
  GPIO_PORTE_DEN_REG |= 0x30;
    
  SYSCTL_RCC_REG |= (1<<20); // Enable PWM Clock Divisor
  SYSCTL_RCC_REG |= 0x000E0000; //  Freq/Div
    
  //Disable the PWM0 Signal 
  PWM0_2_CTL_R &=~ (1<<0);  
  //select the counting mode
  PWM0_2_CTL_R &=~ 0x00000002;  
  /*
  Adjusting the actions of the signal for PE4 and PE5
  (PWMA high when counter matches PWM0LOAD and PWMA Low when counter matches PWM0CMPA) 
  */
  PWM0_2_GENA_R = 0x0000008C;
  PWM0_2_GENB_R = 0x0000080C;
}

/* Initialization of motors module */
void motor_init()
{
     volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x08;            /* enable clock to PORTD */
    delay = SYSCTL_REGCGC2_REG;
    GPIO_PORTD_AMSEL_REG &= ~(0x03);         /* Disable Analog*/
    GPIO_PORTD_PCTL_REG  &= ~(0x000000FF);   /* Clear PMCx bits for PF1 to use it as GPIO pin */
    GPIO_PORTD_DIR_REG   |= 0x03;       /* Configure PF1 as output pin */
    GPIO_PORTD_AFSEL_REG &= ~(0x03);      /* Disable alternative function */
    GPIO_PORTD_DEN_REG   |= 0x03;       /* Enable Digital I/O */
    GPIO_PORTD_DATA_REG  &= ~(0x03);      /* Clear bits */
    
    delay = 0;
    SYSCTL_REGCGC2_REG |= 0x10;  /* enable clock to PORTE */
    delay = SYSCTL_REGCGC2_REG;
    GPIO_PORTE_AMSEL_REG &= ~(0x06);         /* Disable Analog*/
    GPIO_PORTE_PCTL_REG  &= ~(0x00000FF0);   /* Clear PMCx bits for PE1 and PE2 to use it as GPIO pin */
    GPIO_PORTE_DIR_REG   |= (0x06);       /* Configure PF1 as output pin */
    GPIO_PORTE_AFSEL_REG &= ~(0x06);      /* Disable alternative function */
    GPIO_PORTE_DEN_REG   |= (0x06);       /* Enable Digital I/O */
    GPIO_PORTE_DATA_REG  &= ~(0x06);      /* Clear bits */
}

/* Initialization of buzzer */
void buzzer_init()
{
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x08;  /* enable clock to PORTD */
    delay = SYSCTL_REGCGC2_REG;
    GPIO_PORTD_AMSEL_REG &= ~(0x04);         /* Disable Analog*/
    GPIO_PORTD_PCTL_REG  &= ~(0x04);       /* Clear PMCx bits for PB0 to use it as GPIO pin */
    GPIO_PORTD_DIR_REG   |= 0x04;       /* Configure PF1 as output pin */
    GPIO_PORTD_AFSEL_REG &= ~(0x04);      /* Disable alternative function */
    GPIO_PORTD_DEN_REG   |= 0x04;       /* Enable Digital I/O */
    GPIO_PORTD_DATA_REG  &= ~(0x04);     /* Clear bits */    
}

/* Initialization of LED */
void LED_init()
{
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x20;  /* enable clock to PORTF */
    delay = SYSCTL_REGCGC2_REG;
    GPIO_PORTF_AMSEL_REG &= ~(0x08);         /* Disable Analog*/
    GPIO_PORTF_PCTL_REG  &= ~(0x08);       /* Clear PMCx bits for PB0 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= 0x08;       /* Configure PF1 as output pin */
    GPIO_PORTF_AFSEL_REG &= ~(0x08);      /* Disable alternative function */
    GPIO_PORTF_DEN_REG   |= 0x08;       /* Enable Digital I/O */
    GPIO_PORTF_DATA_REG  &= ~(0x08);     /* Clear bits */
}

/* Initialization of timer 0 for ultrasonic*/
void Timer0_init()
{
    SYSCTL_RCGCTIMER_REG |= 0x01;
    TIMER0_GPTMCTL_REG = 0x00;
    TIMER0_GPTMCFG_REG |= 0x04;
    TIMER0_GPTMTAMR_REG = 0x17; //up count, capture mode timer and edge time mode
    TIMER0_GPTMTAPR_REG = 0;
    TIMER0_GPTMICR_REG |= 0x04;
    TIMER0_GPTMIMR_REG |= 0x05;
    NVIC_EN0_REG = 1<<19;
    TIMER0_GPTMCTL_REG |= 0x0C;
    TIMER0_GPTMCTL_REG |= (1<<0);    
}

/* Initialization of ultrasonic */
void Ultrasonic_Init()
{
    //initiation of Pin PD3
  volatile unsigned long delay = 0;
  SYSCTL_REGCGC2_REG |= (1<<3);
  delay = SYSCTL_REGCGC2_REG;
  GPIO_PORTB_AMSEL_REG = 0;
  GPIO_PORTB_PCTL_REG &= 0xFFFF0FFF;
  GPIO_PORTB_DIR_REG |= 0x08;
  GPIO_PORTB_AFSEL_REG &=~ 0x08;
  GPIO_PORTB_DEN_REG |= 0x08;
  
  //initiation of Pin PF0 
  volatile unsigned long delay1 = 0;
  SYSCTL_REGCGC2_REG |= (1<<5);
  delay1 = SYSCTL_REGCGC2_REG;
  GPIO_PORTF_LOCK_REG |= 0x4C4F434B;
  GPIO_PORTF_CR_REG |= (1<<0);
  GPIO_PORTF_AMSEL_REG = 0;
  GPIO_PORTF_PCTL_REG &= 0xFFFFFFF0;
  GPIO_PORTF_DIR_REG &=~ 0x01;
  GPIO_PORTF_AFSEL_REG |= 0x01;
  GPIO_PORTF_PCTL_REG |= 0x00000007;
  GPIO_PORTF_DEN_REG |= 0x01;
  
  Timer0_init();
}

/* Initialization of EEPROM */
uint8 EEPROM_init()
{
    volatile uint8 delay = 0;
    EEPROM_RCGCEEPROM_REG |= 0x01;              /*Enable EEPROM clock module*/
    while(delay < 6) {delay++;}                  /* Waiting 6 cycles */
    while(EEPROM_EEDONE_REG & (0x01) == 1);     /* Wait untill working bit is cleared.*/
    if((EEPROM_EESUPP_REG & (0x8) == 8) || (EEPROM_EESUPP_REG & (0x4) == 4))      /* Checking if isn't an error ocurred*/
      return FALSE;
    //EEPROM_SREEPROM_REG |= 0x01;                /*Reset the EEPROM module*/
    delay = 0;
    while(delay < 6) {delay++;}                  /* Waiting 6 cycles */
    while(EEPROM_EEDONE_REG & (0x01) == 1);     /* Wait untill working bit is cleared.*/
    if((EEPROM_EESUPP_REG & (0x8) == 8) || (EEPROM_EESUPP_REG & (0x4) == 4))      /* Checking if isn't an error ocurred*/
      return FALSE;
    EEPROM_enable();
    return TRUE;
}

/* Initialization of GPT systick timer for OS */
void SysTick_Start(uint16 Tick_Time)
{
    SYSTICK_CTRL_REG    = 0;                         /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = 15999 * Tick_Time;         /* Set the Reload value to count n miliseconds */
    SYSTICK_CURRENT_REG = 0;                         /* Clear the Current Register value */
    /* Configure the SysTick Control Register 
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x07;
    /* Assign priority level 3 to the SysTick Interrupt */
    NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);
}


/* initialization function */
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
	
	/* Initialize SysTick timer by 250ms per interrupt */
	SysTick_Start(250);
}



int main()
{
	Init_Task();
    double lat[]={30.0808057,30.08091665,30.0814977,30.0819667,30.0821707};
    double lon[]={31.2792949,31.2794067,31.2796677,31.2804731,31.2806612};
	
}
