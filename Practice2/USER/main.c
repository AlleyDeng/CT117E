#include <stdio.h>
#include "stm32f10x.h"
#include "lcd.h"
#include "adc.h"
#include "led.h"
#include "rtc.h"

uint8_t string[20];
uint8_t timeDisplayFlag = 0;
uint8_t adcDisplayFlag = 0;
uint32_t timingDelay = 0;
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
	NVIC_SetPriority(SysTick_IRQn, 0);
	STM3210B_LCD_Init();
	LCD_Clear(White);
	ADC_Config();
	LED_Config();
	RTC_Config();
	
	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RTC_SetCounter(23*3600+59*60+55);
	
	while (1) {
		if (adcDisplayFlag == 1) {
			sprintf (string, "     V1:%.2f", Read_ADC());	
			LCD_DisplayStringLine(Line3, string);
			if (Read_ADC() > vdd*k) {
				LED_Control(LEDALL, 0);
				LED_Control(LED1, 1);
				DelayMs(200);
				LED_Control(LED1, 0);
				DelayMs(200);
			}
			adcDisplayFlag	= 0;		
		}
	}
}