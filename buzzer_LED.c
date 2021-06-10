 /******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for buzzer.
 ******************************************************************************/

#include "buzzer_LED.h"

/* LED on PF3, Buzzer on PD2 */

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

void buzzer_on()
{
  SET_BIT(GPIO_PORTD_DATA_REG, 2);
}

void buzzer_off()
{
  CLEAR_BIT(GPIO_PORTD_DATA_REG, 2);
}

void LED_on()
{
  SET_BIT(GPIO_PORTF_DATA_REG, 3);
}

void LED_off()
{
  CLEAR_BIT(GPIO_PORTF_DATA_REG, 3);
}
