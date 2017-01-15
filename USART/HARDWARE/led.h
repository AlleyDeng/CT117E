#ifndef _LED_H_
#define _LED_H_
#include "stdint.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define LED0 GPIO_Pin_8
#define LED1 GPIO_Pin_9
#define LED2 GPIO_Pin_10
#define LED3 GPIO_Pin_11
#define LED4 GPIO_Pin_12
#define LED5 GPIO_Pin_13
#define LED6 GPIO_Pin_14
#define LED7 GPIO_Pin_16
#define LEDALL GPIO_Pin_All

void LED_Init(void);
void LED_Control(uint16_t LED, uint8_t LED_Status);


#endif

