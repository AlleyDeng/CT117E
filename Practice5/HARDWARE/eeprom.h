#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "stm32f10x.h"
#include "i2c.h"

uint8_t AT24C02_Read(uint8_t address);
void AT24C02_Write(uint8_t address, uint8_t info);



#endif
