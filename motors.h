 /******************************************************************************
 *
 * Module: motors
 *
 * File Name: motors.h
 *
 * Description: Header file for motor.
 ******************************************************************************/

#ifndef MOTORs_H_
#define MOTORs_H_

/* PE4, PE5 for PWM signal
   PD0, ,PD1 for motor 1
   PE1, ,PE2 for motor2
*/

#include "tm4c123gh6pm_registers.h"
#include "Platform_Types.h"

void motor_init();
void change_speed(uint8 speed);
void move_backward();
void move_forward();
void move_right();
void move_left();
void stop_car();


#endif /* MOTORs_H_ */