#include "stm32f10x.h"
#include "lcd.h"
#include "exti.h"
uint32_t TimingDelay = 0;
uint8_t string[20];

void DelayMs(uint32_t nTime)
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}

int main (void)
{
	SysTick_Config(SystemCoreClock/ 1000);
	NVIC_SetPriority (SysTick_IRQn, 1);
	EXTI_Config();
	STM3210B_LCD_Init();
	LCD_Clear(White);
	while (1) {
		
	}
}




	