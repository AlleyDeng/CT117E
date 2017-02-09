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
	unsigned char Res;
	extern unsigned char str[20];
	static int i = 0;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {	/* 接收到数据 */
		Res = USART_ReceiveData(USART2);
		if (Res == '\r' || Res == '\0' || Res == '\n') {
			str[i] = 0;	
			i = 0;
			USART_SendString(str);
			LCD_DisplayStringLine(Line1, str);			
		}	else {
			str[i++] = Res;
		}
	}
}
