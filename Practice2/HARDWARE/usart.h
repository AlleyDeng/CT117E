#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"

void USART_Config(void);
void USART_SendString(uint8_t *string);

#endif
