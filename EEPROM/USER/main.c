#include <stdio.h>
#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"
#include "i2c.h"
#include "eeprom.h"

uint32_t TimingDelay = 0;

void Delay_ms(uint32_t nTime)	
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}

int main (void)
{
	uint8_t temp = 0;
	uint8_t string[20];
	x24c02_Write(0x21, 0);
	SysTick_Config(SystemCoreClock / 1000);
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LCD_DisplayStringLine(Line1, "      I2C DEMO      ");
	LCD_DisplayStringLine(Line2, "     AT24C02 R/W    ");
	
	i2c_init();
	temp = x24c02_Read(0x21);
	x24c02_Write(0x21, temp + 1);
	
	sprintf(string, "%s%d", "  ADDR:0xFF,VAL:", temp);
	LCD_DisplayStringLine(Line6, string);
	
	while (1) {
	}
}


