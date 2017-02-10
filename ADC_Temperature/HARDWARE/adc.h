#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"

extern void DelayMs(unsigned int nTime);
void ADC_Config(void);
float Read_Temperature(void);









#endif
