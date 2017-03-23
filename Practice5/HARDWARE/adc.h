#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"
#include "adc.h"

void ADC_Config(void);

float Read_ADC(void);

extern void DelayMs(uint32_t nTime);




#endif
