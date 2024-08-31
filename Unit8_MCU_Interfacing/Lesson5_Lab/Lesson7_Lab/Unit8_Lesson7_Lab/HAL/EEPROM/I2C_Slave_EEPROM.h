/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Aug 30, 2024
 *      Author: Ahmed Aseel
 */

#ifndef EEPROM_I2C_SLAVE_EEPROM_H_
#define EEPROM_I2C_SLAVE_EEPROM_H_

#include "STM32F103C6_I2C_driver.h"

#define EEPROM_ADDRESS					0x2A

//APIS
void EEPROM_Init(void);
void EEPROM_Write_NBytes(uint16_t memAddress, uint8_t *bytes, uint8_t dataLen);
void EEPROM_Read_NBytes(uint16_t memAddress, uint8_t *bytes, uint8_t dataLen);

#endif /* EEPROM_I2C_SLAVE_EEPROM_H_ */
