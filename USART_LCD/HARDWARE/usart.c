#include"USART.h"

void USART_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	/* USART2 Tx引脚配置 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USART2 Rx引脚配置 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USART2 NVIC配置 */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	/* 抢占优先级3 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			/* 子优先级3 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				
	NVIC_Init(&NVIC_InitStructure);
	
	/* USART2 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 19200;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART_InitStructure);
	
	USART_Cmd(USART2, ENABLE);						/* 使能串口 */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	/* 开启串口接受中断 */
}

void USART_SendString(unsigned char *str)
{
	unsigned int index = 0;
	
	while (str[index] != 0) {
		USART_SendData(USART2, str[index]);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		index ++;
	}	
}	

void USART2_IRQHandler(void)
{ 
	uint8_t temp;
	
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		temp = USART_ReceiveData(USART2);
		if ((temp == '#') || (RXCUNT == 20)) {
			RXCUNT = 0;
			RXOVER = 1;	/* 接收完成标志 */
			USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
		}	else {
			USART_RXBUF[RXCUNT++] = temp;
//			RXCUNT++;
		}
	}
}
