#include "eeprom.h"

/**
  *@brief	��AT24C02ָ����ַ����һ���ֽ�����
  *@param	address AT24C02�ڲ��洢����
  *@retval	val ��������
  */
uint8_t AT24C02_Read(uint8_t address)
{
	unsigned char val;
	
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	
	I2CSendByte(address);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(0xa1);
	I2CWaitAck();
	val = I2CReceiveByte();
	I2CWaitAck();
	I2CStop();
	
	return val;
}

/**
  *@brief	��AT24C02ָ����ַд��һ���ֽ�����
  *@param	address	AT24C02�ڲ��洢��ַ
  *@param	info	д������
  *@retval 	none
  */
void AT24C02_Write(unsigned char address, unsigned char info)
{
	I2CStart();
	I2CWaitAck();
	I2CSendByte(0xa0);
	I2CWaitAck();
	
	I2CSendByte(address);
	I2CWaitAck();
	I2CSendByte(info);
	I2CWaitAck();
}


