#include <stdio.h>
#include "stm32f10x.h"
#include "lcd.h"
#include "adc.h"
#include "led.h"
#include "rtc.h"
#include "key.h"
#include "usart.h"

uint8_t lcdString[20];
uint8_t RxBuffer[20];
uint8_t TxBuffer[20];
uint8_t RxCounter = 0;
uint8_t RxStatus = 0;
uint8_t timeDisplayFlag = 0;
uint8_t adcDisplayFlag = 0;
uint8_t ledWorkFlag = 1;
uint8_t sendValtageFlag = 1;
uint32_t timingDelay = 0;
uint32_t sendValtageTime = 23*3600+59*60+58;
float k = 0.5;
float vdd = 3.3;

void DelayMs(uint32_t nTime)
{
	timingDelay = nTime;
	while (timingDelay != 0);
}

int main (void)
{
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_SetPriority(SysTick_IRQn, 0);
	STM3210B_LCD_Init();
	LCD_Clear(White);
	ADC_Config();
	LED_Config();
	RTC_Config();
	KEY_Config();
	USART_Config();
	
	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RTC_SetCounter(23*3600+59*60+55);
	
	while (1) {
		if (adcDisplayFlag == 1) {
			sprintf (lcdString, "     V1:%.2f       ", Read_ADC());	
			LCD_DisplayStringLine(Line3, lcdString);
			if (Read_ADC() > vdd*k && ledWorkFlag == 1) {
				LCD_DisplayStringLine(Line5, "     LED:ON         ");
				LED_Control(LEDALL, 0);
				LED_Control(LED1, 1);
				DelayMs(200);
				LED_Control(LED1, 0);
				DelayMs(200);
			}	else {
				LCD_DisplayStringLine(Line5, "     LED:OFF        ");
			}
			adcDisplayFlag	= 0;		
		}
		sprintf(lcdString, "     K:%.1f           ", k);
		LCD_DisplayStringLine(Line4, lcdString);	
		if (RTC_GetCounter() == sendValtageTime && sendValtageFlag == 1) {
			sprintf(TxBuffer, "%.2f+%.1f%.2d%.2d%.2d\n", Read_ADC(), k, sendValtageTime/3600, 
							(sendValtageTime % 3600) / 60, (sendValtageTime % 3600) % 60);
			USART_SendString(TxBuffer);
			sendValtageFlag = 0;
		}	
	}
}
