#include <stdio.h>
#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"
#include "adc.h"

uint32_t TimingDelay = 0;
uint8_t ADC_Flag;

void DelayMs(uint32_t nTime)	
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}

int main (void)
{
	float adc_temp;
	char string[20];
	SysTick_Config(SystemCoreClock/1000);	/* 1ms÷–∂œ“ª¥Œ */
	LED_Init();
	ADC_Config();
	STM3210B_LCD_Init();
	LCD_Clear(White);
	
	LCD_DisplayStringLine(Line1, "      ADC DEMO     ");
	LCD_DisplayStringLine(Line3, " PB0-ADC channel 8  ");
	
	while (1) {
		if (ADC_Flag) {
			ADC_Flag = 0;
			adc_temp = Read_ADC();
			sprintf(string, "%s%.3f", "  ADC Value:", adc_temp);
			LCD_DisplayStringLine(Line7, string);
		}
	}		
}
