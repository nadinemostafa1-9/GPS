 /******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: EEPROM.h
 *
 * Description: Header file for EEPROM.
 *
 ******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "tm4c123gh6pm_registers.h"
#include "./Platform_Types.h"

#include "stdint.h"

void PeripheralEnable(uint32_t ui32Peripheral);

boolean EEPROM_init(void);
void EEPROM_enable(void);
int EEPROM_erase(int block_count);
int EEPROM_write(const uint32 *data, uint16 word_count);
void EEPROM_read(uint32 *data,uint32 word_count);

#endif /* EEPROM_H_ */
