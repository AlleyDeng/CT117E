#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "beep.h"
#include "usart.h"

uint32_t nTimingDelay = 0;
uint32_t RxCounter = 0;
uint8_t keyTemp = 0;
uint8_t string[20];
uint8_t RxBuffer[20];
uint8_t RxFlag = 0;
int packingSpace = 10;

void DelayMs(uint32_t nTime)	
{
	nTimingDelay = nTime;
	while (nTimingDelay != 0);
}

int main (void)
{
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_SetPriority(SysTick_IRQn, 0);
	LED_Config();
	Key_Config();
	Beep_Config();
	Usart_Config();
	STM3210B_LCD_Init();
	/* Configure the NVIC Preemption Priority Bits */
	
	LED_Control(LEDALL, 0);
	Usart_SendString("Input command:\n");
	
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	LCD_Clear(Blue);
	
	sprintf(string, "%s%d%c", " packingSpace : ", packingSpace, ' ');
	LCD_DisplayStringLine(Line1, string);
	
	while (1) {
		GPIO_SetBits(GPIOB, GPIO_Pin_4);
	}
}
