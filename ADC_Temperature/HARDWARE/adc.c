#include "adc.h"

/**
  *@brief  ADC时钟源及工作模式配置
  *@param  None
  *@retval None
  */
void ADC_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode =DISABLE;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);
	ADC_TempSensorVrefintCmd(ENABLE);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1));
}

float Read_Temperature(void)
{
	uint16_t tempdata;
	float temperature;
	float volt;
	
/*  Current Temperature = (V25-Vsensor)/AVG_SLOP + 25    */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	DelayMs(5);
	tempdata = ADC_GetConversionValue(ADC1);
	volt = tempdata*3.30/0xfff;
	temperature = (1430 - 1000*volt)/4.3 + 25;
	
	return temperature;
}


