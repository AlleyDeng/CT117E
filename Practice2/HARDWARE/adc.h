#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"

extern void DelayMs(uint32_t nTime);

void ADC_Config(void);
float Read_ADC(void);


#endif
 