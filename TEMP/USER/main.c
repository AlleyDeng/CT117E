#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"
#include "timer.h"

uint32_t Channel2Pulse = 3000;
uint32_t Channel3Pulse = 1000;
uint32_t TimingDelay = 0;
unsigned int n50Ms;
unsigned int num;

void DelayMs(uint32_t nTime)	
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}

int main (void)
{
	LED_Init();
	TIMER_Config();
	while (1) {
		LED_Control(LEDALL, 1);
	}		
}
