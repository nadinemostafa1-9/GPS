/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: Ultrasonic.c
 *
 * Description: source file for the Ultrasonic driver
 *
 *
 *******************************************************************************/

#include "Ultrasonic.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void Pins_Init()
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
  
}


void Ultrasonic_Init()
{
  Pins_Init();
  Timer0_init();
}

void Ultrasonic_startTrigger()
{
  /* Given 10us trigger pulse */
  GPIO_PORTD_DATA_REG &= ~(1<<3); /* make trigger  pin low */
  Delay_MS(0.001); /*10 seconds delay */
  GPIO_PORTD_DATA_REG |= (1<<3); /* make trigger  pin high */
  Delay_MS(0.001); /*10 seconds delay */
  GPIO_PORTD_DATA_REG &= ~(1<<3); /* make trigger  pin low */
  Delay_MS(0.001); /*10 seconds delay */
  GPIO_PORTD_DATA_REG |= (1<<3); /* make trigger  pin high */
}

uint8 measure_distance()
{
  uint32 Pulse_Duration = lastEdge - thisEdge;
  uint32 distance = (Pulse_Duration * 340000)/(2 * 1000000);
  return distance;
}
