 /******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: EEPROM.c
 *
 * Description: Source file for EEPROM.
 *
 ******************************************************************************/

#include "EEPROM.h"

static uint16 flashkey=0;


#define SYSCTL_RCGCBASE   0x400fe600
#define HWREG(x)	   (*((volatile uint32_t *)(x)))


#define HWREGBITW(x,b)		HWREG(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                     \
              (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))

void PeripheralEnable(uint32_t ui32Peripheral)
{
    //
    // Check the arguments.
    //
    //ASSERT(_SysCtlPeripheralValid(ui32Peripheral));

    //
    // Enable this peripheral.
    //
    HWREGBITW(SYSCTL_RCGCBASE + ((ui32Peripheral & 0xff00) >> 8),
              (ui32Peripheral & 0xff)) = 1;
}

boolean EEPROM_init()
{
    volatile uint32 delay = 0;
    while(delay < 60000) {delay++;}   
    delay = 0;
    //while((EEPROM_EEDONE_REG & (0x01)) == 1) {} 
    EEPROM_RCGCEEPROM_REG |= 0x01;              /*Enable EEPROM clock module*/
    while(delay < 60) {delay++;}                  /* Waiting 6 cycles */
    while((EEPROM_EEDONE_REG & (0x01)) == 1);     /* Wait untill working bit is cleared.*/
    if(((EEPROM_EESUPP_REG & (0x8)) == 8) || ((EEPROM_EESUPP_REG & (0x4)) == 4))      /* Checking if isn't an error ocurred*/
      return FALSE;
    EEPROM_SREEPROM_REG |= 0x01;                /*Reset the EEPROM module*/
    delay = 0;
    while(delay < 6) {delay++;}                  /* Waiting 6 cycles */
     EEPROM_SREEPROM_REG &= ~(0x01);                /*Reset the EEPROM module*/
    while((EEPROM_EEDONE_REG & (0x01)) == 1);     /* Wait untill working bit is cleared.*/
    if(((EEPROM_EESUPP_REG & (0x8)) == 8) || ((EEPROM_EESUPP_REG & (0x4)) == 4))      /* Checking if isn't an error ocurred*/
      return FALSE;
    EEPROM_enable();
    return TRUE;

}
void EEPROM_enable(){

if(EEPROM_BOOTCFG_REG &(0x10))flashkey=0xA442;
else flashkey=0x71D5;

}


int EEPROM_erase(int block_count){
    int i;
    if(flashkey==0)return (int)-1;
    for(i=0;i<block_count;i++){
        EEPROM_FMA_REG |=((uint32)EEPROM_BASE_ADDRESS)+(i*1024);
        EEPROM_FMC_REG=(flashkey<<16)|(0x2);
        while(EEPROM_FMC_REG &0x02){}
    }

return 0;
}

int EEPROM_write(const uint32 *data, uint16 word_count)
{
    int i;
    int block_count;
    if(flashkey==0)return -1;
    block_count=((word_count*sizeof(uint32))/1024)+1;
    EEPROM_erase(block_count);
    for(i=0;i<word_count;i++)
    {
          //set the data register with the word to be written
          EEPROM_FMD_REG = ((volatile uint32 *)data)[i];
          //clear then set the offset address field with write address
          EEPROM_FMA_REG&=0xFFFC0000;
          EEPROM_FMA_REG|=(uint32)EEPROM_BASE_ADDRESS+(i*sizeof(uint32));
          // trigger write operation
          EEPROM_FMC_REG=(flashkey<<16)|(0x1);
          //poll until write bit is cleared
          while(EEPROM_FMC_REG&0x1) {} 
    }
    return 0;

}
void EEPROM_read(uint32 *data,uint32 word_count){
      int i;
      for(i=0;i<word_count;i++){
            //copy the count of bytes into data buffer
            *((( uint32 *)data)+i) = EEPROM_BASE_ADDRESS[i];
      }
}
/*********************************************************************************************/