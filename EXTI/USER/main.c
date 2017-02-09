#include "stm32f10x.h"
#include "lcd.h"

unsigned int TimingDelay = 0;

void DelayMs(unsigned int nTime)
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}

int main (void)
{
	SysTick_Config(SystemCoreClock/ 1000);
	STM3210B_LCD_Init();
	
	while (1) {
		
	}
}


	