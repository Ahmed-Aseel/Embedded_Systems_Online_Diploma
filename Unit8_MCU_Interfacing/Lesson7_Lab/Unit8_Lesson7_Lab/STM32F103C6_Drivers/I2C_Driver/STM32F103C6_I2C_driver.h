/*
 * STM32F103C6_I2C_driver.h
 *
 *  Created on: Mar 1, 2023
 *      Author: Ahmed Aseel
 */

#ifndef I2C_DRIVER_STM32F103C6_I2C_DRIVER_H_
#define I2C_DRIVER_STM32F103C6_I2C_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref Device_Mode_define
//I2C_CR1 Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define Device_Mode_I2C		    			(uint8_t)(0)
#define Device_Mode_SMBus					(uint8_t)(1<<1)

//@ref I2C_SCLK
//Standard Speed (up to 100 kHz)
//Fast Speed (up to 400 kHz)
//Program the peripheral input clock in I2C_CR2.FREQ[5:0] in order to generate correct timings
//Configure the clock control registers I2C_CCR SM or FM, Thigh = Tlow = CCR * TPCLK1
//Configure the rise time register I2C_TRISE
#define I2C_SCLK_SM_50K						(50000UL)
#define I2C_SCLK_SM_100K					(100000UL)
#define I2C_SCLK_FM_200K					(200000UL) // Fast mode not supported yet
#define I2C_SCLK_FM_400K					(400000UL) // Fast mode not supported yet

//@ref Stretch_Mode_define
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until it is reset by software.
//0: Clock stretching enabled
//1: Clock stretching disabled
#define I2C_STRETCH_MODE_ENABLE		    	(uint8_t)(0)
#define I2C_STRETCH_MODE_DISABLE			(uint8_t)(1<<7)

//@ref Addressing_Slave_Mode
//I2C_OAR1 Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_ADDRESSING_SLAVE_MODE_7BITS		(uint16_t)(0)
#define I2C_ADDRESSING_SLAVE_MODE_10BITS	(uint16_t)(1<<15)

//@ref Dual_Address_define
#define I2C_DUAL_ADDRESS_DISABLE			0
#define I2C_DUAL_ADDRESS_ENABLE		    	1

//@ref I2C_ACK
//I2C_CR1 Bit 10 ACK: Acknowledge enable
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_DISABLE						(uint16_t)(0)
#define I2C_ACK_ENABLE						(uint16_t)(1<<10)

//@ref I2C_ENGC
//I2C_CR1 Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.
#define I2C_ENGC_DISABLE					(uint8_t)(0)
#define I2C_ENGC_ENABLE		    			(uint8_t)(1<<6)

//-----------------------------
//User type definitions (structures)
//-----------------------------

struct S_I2C_Slave_Address
{
	uint16_t I2C_Addressing_Slave_Mode;  // This parameter can be a value of @ref Addressing_Slave_Mode
										 // If Dual_Address_Status is enabled then Addressing_Mode must be 7-Bits
	uint8_t Dual_Address_Status       ;  // This parameter can be a value of @ref Dual_Address_define
	uint16_t Primary_Slave_Address    ;
	uint16_t Secondary_Slave_Address  ;
};

typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_MATCH,
	I2C_EV_DATA_REQ,
	I2C_EV_DATA_REC
}Slave_State_t;

typedef struct
{
	uint8_t Device_Mode                     ; // Specifies the operating mode I2C or SMBus.
							                  // This parameter can be a value of @ref Device_Mode_define

	uint32_t Clock_Speed                    ; // Specifies the I2C clock frequency.
							                  // This parameter can be a value of @ref I2C_SCLK

	uint8_t Stretch_Mode                    ; // This parameter can be a value of @ref Stretch_Mode_define

	struct S_I2C_Slave_Address Slave_Address;

	uint16_t Ack_Control                    ; // This parameter can be a value of @ref I2C_ACK

	uint8_t General_Call_Address_Detection  ; // This parameter can be a value of @ref I2C_ENGC

	void (*p_Slave_Event_CallBack)(Slave_State_t state); // Set slave callback function

}I2C_Config_t;

typedef enum {WITH_STOP, WITHOUT_STOP} Stop_Condition;

typedef enum {START, REPETED_START} Repeted_Start;

typedef enum {DISABLE, ENABLE} FunctionalState;

typedef enum {RESET, SET} FlagStatus;

typedef enum {I2C_DIRECTION_WRITE, I2C_DIRECTION_READ} I2C_Direction;

typedef enum
{
	I2C_FLAG_BUSY,
	EV5,   // EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6,   // EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
    EV7,   // RXNE=1 CLEARD BY READING DR REGISTER
	EV8,   // EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_1, // EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	MASTER_BYTE_TRANSMITTING = ((uint32_t) 0x00070080) //TRA, BUSY, TXE, MSL, TXE flags
}Status;

/*
* ===============================================
* APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/

void MCAL_I2C_Init(I2C_TypeDef *I2Cx, I2C_Config_t *I2CConfig);
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx );
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef *I2Cx);

// Master polling mechanism
void MCAL_I2CMaster_Transmite(I2C_TypeDef *I2Cx, uint16_t devAddr, uint8_t* data,
							  uint8_t dataLen, Stop_Condition stop, Repeted_Start start);

void MCAL_I2CMaster_Receive(I2C_TypeDef *I2Cx, uint16_t devAddr, uint8_t* data,
							  uint8_t dataLen, Stop_Condition stop, Repeted_Start start);

// Slave interrupt mechanism
void MCAL_I2CSlave_Transmite(I2C_TypeDef *I2Cx, uint8_t data);
uint8_t MCAL_I2CSlave_Receive(I2C_TypeDef *I2Cx);

#endif /* I2C_DRIVER_STM32F103C6_I2C_DRIVER_H_ */
