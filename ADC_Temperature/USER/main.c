#include <stdio.h>
#include "adc.h"
#include "led.h"
#include "lcd.h"

uint32_t nTimingDelay;
uint8_t ADC_Flag;

void DelayMs(unsigned int nTime)
{
	nTimingDelay = nTime;
	while (nTimingDelay != 0);
}

int main (void)
{
	uint8_t string[20];
	float t_temp;
	
	SysTick_Config(SystemCoreClock / 1000);
	ADC_Config();
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	
	LCD_DisplayStringLine(Line1, "      ADC DEMO      ");
	LCD_DisplayStringLine(Line2, " PB0-ADC channel 8 ");
	
	while (1) {
		if (ADC_Flag == 1) {
			ADC_Flag = 0;
			t_temp = Read_Temperature();
			sprintf(string, "%s%.3f", "Tempetature:", t_temp);
			LCD_DisplayStringLine(Line7, string);
		}
	}
}
