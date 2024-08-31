/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Aug 30, 2024
 *      Author: Ahmed Aseel
 */

#include "I2C_Slave_EEPROM.h"

void EEPROM_Init(void)
{
	//================ I2C1 INIT ====================
	// SCL -------> PB6
	// SDA -------> PB7

	// I2C Controller act as a master
	I2C_Config_t I2C_cfg;
	I2C_cfg.Device_Mode = Device_Mode_I2C;
	I2C_cfg.Stretch_Mode = I2C_STRETCH_MODE_ENABLE;
	I2C_cfg.General_Call_Address_Detection = I2C_ENGC_ENABLE;
	I2C_cfg.Clock_Speed = I2C_SCLK_SM_100K;
	I2C_cfg.Ack_Control = I2C_ACK_ENABLE;
	I2C_cfg.p_Slave_Event_CallBack = NULL;

	MCAL_I2C_Init(I2C1, &I2C_cfg);
	MCAL_I2C_GPIO_Set_Pins(I2C1);
}

void EEPROM_Write_NBytes(uint16_t memAddress, uint8_t *bytes, uint8_t dataLen)
{
	uint8_t i = 0;
	uint8_t buffer[256];
	buffer[0] = (uint8_t)(memAddress >> 8);	//high address
	buffer[1] = (uint8_t)(memAddress);		//low address

	for(i = 2; i < (dataLen+2); i++)
	{
		buffer[i]= bytes[i-2];
	}

	MCAL_I2CMaster_Transmite(I2C1, EEPROM_ADDRESS, buffer, (dataLen+2), WITH_STOP, START);
}

void EEPROM_Read_NBytes(uint16_t memAddress, uint8_t *bytes, uint8_t dataLen)
{
	uint8_t buffer[2];
	buffer[0] = (uint8_t)(memAddress >> 8);	//high address
	buffer[1] = (uint8_t)(memAddress);		//low address

	MCAL_I2CMaster_Transmite(I2C1, EEPROM_ADDRESS, buffer, 2, WITHOUT_STOP, START);
	MCAL_I2CMaster_Receive(I2C1, EEPROM_ADDRESS, bytes, dataLen, WITH_STOP, REPETED_START);
}
