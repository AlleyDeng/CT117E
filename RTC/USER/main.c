#include <stdio.h>
#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"
#include "rtc.h"

uint32_t TimingDelay = 0;
uint8_t timeDisplay = 0;

void DelayMs(uint32_t nTime) 
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}

int main (void)
{
	SysTick_Config(SystemCoreClock/1000);
	NVIC_SetPriority(SysTick_IRQn, 0);
	
	LED_Config();
	RTC_Config();
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(White);
	
	LCD_DisplayStringLine(Line1, "      RTC DEMO      ");
	
	while (1) {
		LED_Control(LEDALL, 0);
		LED_Control(LED0, 1);
		LED_Control(LED7, 1);
		if (timeDisplay == 1) {
			timeDisplay = 0;
			TimeDisplay(RTC_GetCounter());
		}
	}
	
}
