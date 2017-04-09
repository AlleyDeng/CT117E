#include "eeprom.h"

/**
  *@brief	从AT24C02指定地址读出一个字节数据
  *@param	address AT24C02内部存储数据
  *@retval	val 读出数据
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
  *@brief	向AT24C02指定地址写入一个字节数据
  *@param	address	AT24C02内部存储地址
  *@param	info	写入数据
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


