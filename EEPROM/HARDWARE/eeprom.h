#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "i2c.h"
#include "stm32f10x.h"

uint8_t x24c02_Read(uint8_t address);
void x24c02_Write(uint8_t address, uint8_t info);























#endif
