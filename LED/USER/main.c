#include "stm32f10x.h"
#include "LED.h"

int main (void)
{
	unsigned int i = 0;
	LED_Init();
	LED_Control(LEDALL, 0);
	
	while (1) {
		for (i = 0xCCCCC; i > 0; i--)
			LED_Control(LED0, 1);
		for (i = 0xCCCCC; i > 0; i--)
			LED_Control(LED0, 0);
	}		
}


