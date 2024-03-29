 /******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for buzzer.
 ******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "tm4c123gh6pm_registers.h"
#include "Platform_Types.h"

void buzzer_init();

void LED_init();

void buzzer_on();

void buzzer_off();

void LED_on();

void LED_off();

#endif /* BUZZER_H_ */
