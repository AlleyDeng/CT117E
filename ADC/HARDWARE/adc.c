#include "adc.h"

/**
  *@brief ADC时钟源及工作模式配置
  *@param None
  *@retval None
  */
void ADC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

//	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	/* PB0-ADC channel 8 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* ADC1 工作模式配置 */
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						/* 单通道模式 */
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 				/* 单次转换 */
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; /* 由软件触发启动 */
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				/* 数据右对齐 */
	ADC_InitStructure.ADC_NbrOfChannel = 1;								/* 顺序进行规则转换的ADC通道数目 */
	ADC_Init(ADC1, &ADC_InitStructure);
	 
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_13Cycles5);
	
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register*/
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while (ADC_GetCalibrationStatus(ADC1));
}

/**
  *@brief	读取ADC转换结果
  *@param	None 
  *@retval 	ADC_VALUE:ADC转换结果
  */
float Read_ADC(void)
{
	float ADC_VALUE;
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
	DelayMs(5);
	ADC_VALUE = ADC_GetConversionValue(ADC1)*3.30/0xfff;
	
	return ADC_VALUE;
}
