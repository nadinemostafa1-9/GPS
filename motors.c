 /******************************************************************************
 *
 * Module: motors
 *
 * File Name: motors.c
 *
 * Description: Source file for GPS.
 ******************************************************************************/

/* PE4, PE5 for PWM signal
   PD0, ,PD1 for motor 1
   PE1, ,PE2 for motor2
*/

#include "motors.h"
#include "PWM.h"

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

void change_speed(uint8 speed)
{
    PWM_SET(100 - speed);

}

void move_backward()
{
   PWM_Output_Enable(1);
   PWM_Output_Enable(2);
   CLEAR_BIT(GPIO_PORTD_DATA_REG,0);
   SET_BIT(GPIO_PORTD_DATA_REG, 1);
   CLEAR_BIT(GPIO_PORTE_DATA_REG,1);
   SET_BIT(GPIO_PORTE_DATA_REG, 2);
}

void move_forward()
{
   PWM_Output_Enable(1);
   PWM_Output_Enable(2);
   CLEAR_BIT(GPIO_PORTD_DATA_REG,1);
   SET_BIT(GPIO_PORTD_DATA_REG, 0);
   CLEAR_BIT(GPIO_PORTE_DATA_REG,2);
   SET_BIT(GPIO_PORTE_DATA_REG, 1);
}

void move_right()
{
   PWM_Output_Enable(1);
   PWM_Output_Enable(2);
   SET_BIT(GPIO_PORTD_DATA_REG,0);
   CLEAR_BIT(GPIO_PORTD_DATA_REG, 1);
   CLEAR_BIT(GPIO_PORTE_DATA_REG,2);
   CLEAR_BIT(GPIO_PORTE_DATA_REG, 1); 
}

void move_left()
{
   PWM_Output_Enable(1);
   PWM_Output_Enable(2);
   CLEAR_BIT(GPIO_PORTD_DATA_REG,1);
   CLEAR_BIT(GPIO_PORTD_DATA_REG, 0);
   CLEAR_BIT(GPIO_PORTE_DATA_REG,2);
   SET_BIT(GPIO_PORTE_DATA_REG, 1);    
}

void stop_car()
{
   CLEAR_BIT(GPIO_PORTD_DATA_REG,1);
   CLEAR_BIT(GPIO_PORTD_DATA_REG,0);
   CLEAR_BIT(GPIO_PORTE_DATA_REG,2);
   CLEAR_BIT(GPIO_PORTE_DATA_REG,1);  
   PWM_Output_Disable();
}