/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.c
 *
 * Description: Source file for the PWM driver
 *
 *
 *******************************************************************************/
#include "PWM.h"


/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

uint32 PWM_Freq = 0;
uint32 Load_value = 0;
uint32 CMP_value = 0;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void PINS_Init()
{
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
}

void PWM_init()
{
  // setting the clock of the PWM bit 0 activate the clock of module 0
  SYSCTL_RCGCPWM_REG |= 1;
  volatile unsigned long delay = 0;
  delay = SYSCTL_PRPWM_REG;
  
  PINS_Init();
    
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
  
  PWM_SET(0);
}

void PWM_SET(uint32 Duty_Cycle)
{
  // adjust the Load register values 
  PWM_Freq  = Freq/64;
  Load_value = PWM_Freq/desired_freq;
  CMP_value = (Load_value*Duty_Cycle)/100 ;
  // Insert thge Load value in Load register and count register of PE4 and PE5 
  PWM0_2_LOAD_R = Load_value;
  PWM0_2_COUNT_R = Load_value;
  // Insert the Compare value in Compare register of PE4 and PE5
  PWM0_2_CMPA_R = CMP_value;
  PWM0_2_CMPB_R = CMP_value;
}
void PWM_Output_Enable(uint32 PinNum)
{
  if(PinNum == 1)
  {
    PWM0_ENABLE_R |= 0x10;
  }
  else if(PinNum == 2)
  {
    PWM0_ENABLE_R |= 0x20;
  }
 
    //Enable the PWM0 Signal 
    PWM0_2_CTL_R |= (1<<0);  
}

void PWM_Output_Disable()
{
  // output disable 
  PWM0_ENABLE_R = 0;
}