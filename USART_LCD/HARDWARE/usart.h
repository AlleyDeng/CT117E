#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include "lcd.h"
#include <string.h>

#define MAXDATASIZE 200

extern uint8_t USART_RXBUF[20];
extern uint8_t RXCUNT;
extern uint8_t RXOVER;

void USART_Config(void);
void USART_SendString(unsigned char *str);
char* USART_ReceiveString(void);

extern void DelayMs(unsigned int a);








#endif
