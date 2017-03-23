#include "stm32f10x.h"
#include "lcd.h"
#include "rtc.h"
#include "beep.h"

uint32_t timingDelay = 0;

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
	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);
	LCD_Clear(Blue);
	
	RTC_Config();
	BEEP_Config();
	
	RTC_SetCounter(24*3600-5);
	LCD_DisplayStringLine(Line1, "      LCD DEMO      ");
	
	while (1) {
		
	}
}
	
