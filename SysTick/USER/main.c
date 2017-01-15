#include "led.h"
#include "stm32f10x_it.h"

uint32_t TimingDelay = 0;

void Delay_ms(uint32_t nTime)
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}
	
int main (void)
{
	LED_Init();
	LED_Control(LEDALL, 0);

	SysTick_Config(SystemCoreClock / 1000);	/* 1ms÷–∂œ“ª¥Œ */
	
	while (1) {
		LED_Control(LED1, 1);
		Delay_ms(500);
		LED_Control(LED1, 0);
		Delay_ms(500);
	}
}



