#ifndef _LED_H_
#define _LED_H_

#include "stm32f10x.h"

#define LED0 GPIO_Pin_8
#define LED1 GPIO_Pin_9
#define LED2 GPIO_Pin_10
#define LED3 GPIO_Pin_11
#define LED4 GPIO_Pin_12
#define LED5 GPIO_Pin_13
#define LED6 GPIO_Pin_14
#define LED7 GPIO_Pin_15
#define LEDALL GPIO_Pin_All

void LED_Config(void);
void LED_Control(uint16_t LED, uint8_t LED_Staus);


#endif
