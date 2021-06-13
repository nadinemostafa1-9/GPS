 /******************************************************************************
 *
 * Module: GPT
 *
 * File Name: GPT.c
 *
 * Description: source file for the GPT driver
 *
 *
 *******************************************************************************/
   
   
#include "Timer0_GPTM.h"

int volatile flag = 0;
uint32 volatile lastEdge = 0, thisEdge = 0;
   
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Timer0A_Handler( void )
{
  Timer->ICR |= 0x00000004; 
  Timer0_DutyCycle();  
}

void Timer0_init()
{
    SYSCTL_RCGCTIMER_REG |= 0x01;
    TIMER0_GPTMCTL_REG = 0x00;
    TIMER0_GPTMCFG_REG |= 0x04;
    TIMER0_GPTMTAMR_REG = 0x17; //up count, capture mode timer and edge time mode
    TIMER0_GPTMTAPR_REG = 0;
    TIMER0_GPTMICR_REG |= 0x04;
    TIMER0_GPTMIMR_REG |= 0x04;
    NVIC_EN0_REG = 1<<19;
    NVIC_PRI4_REG = (NVIC_PRI4_REG & 0x1FFFFFFF)|(0x20000000);//setting pariority 1 (31-29)
    TIMER0_GPTMCTL_REG |= 0x0C;
    TIMER0_GPTMCTL_REG |= (1<<0);    
}

void Timer0_DutyCycle()
{
  TIMER0_GPTMICR_REG = 4;
  if (flag == 0)
  {
    lastEdge = TIMER0_GPTMTAR_REG;
    flag++;
  }
  else if(flag == 1)
  {
    thisEdge = TIMER0_GPTMTAR_REG;
    flag = 0;
  }
}
