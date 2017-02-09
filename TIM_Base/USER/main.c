#include <stm32f10x.h>
#include <stdio.h>
#include <stdint.h>
#include "led.h"
#include "lcd.h"
#include "timer.h"

unsigned int n50Ms = 0;
unsigned int num = 0;
unsigned int TimingDelay = 0;

void DelayMs(unsigned int nTimeDelay)
{
	TimingDelay = nTimeDelay;
	while (TimingDelay != 0);
}

int main (void)
{
	char string[20];
	LED_Init();
	TIM_Config();
	SysTick_Config(SystemCoreClock/1000);
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LED_Control(LEDALL, 0);
	while (1) {
		sprintf(string, "%s%d", "    SECONDS:", num);
		LCD_DisplayStringLine(Line2, string);
	}

}
