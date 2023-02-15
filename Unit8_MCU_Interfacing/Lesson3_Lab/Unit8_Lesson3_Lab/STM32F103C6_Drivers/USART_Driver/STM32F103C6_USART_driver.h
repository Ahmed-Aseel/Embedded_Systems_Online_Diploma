/*
 * STM32F103C6_USART_driver.h
 *
 *  Created on: Feb 12, 2023
 *      Author: Ahmed Aseel
 */

#ifndef STM32F103C6_USART_DRIVER_H_
#define STM32F103C6_USART_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_driver.h"
#include "STM32F103C6_RCC_driver.h"

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref USART_Mode_define
#define  USART_Mode_RX   			(uint32_t)(1<<2) // RE = 1
#define  USART_Mode_TX       		(uint32_t)(1<<3) // TE = 1
#define  USART_Mode_TX_RX			(uint32_t)(1<<2 | 1<<3)

//@ref BaudRate_define
#define USART_BaudRate_2400  		2400
#define USART_BaudRate_4800  		4800
#define USART_BaudRate_9600  		9600
#define USART_BaudRate_19200  		19200
#define USART_BaudRate_57600  		57600
#define USART_BaudRate_115200  		115200
#define USART_BaudRate_230400  		230400
#define USART_BaudRate_460800  		460800
#define USART_BaudRate_921600  		921600
#define USART_BaudRate_2250000  	2250000
#define USART_BaudRate_4500000 		4500000

//@ref Payload_Length_define
#define Payload_Length_8B			(uint32_t)(0)
#define Payload_Length_9B			(uint32_t)(1<<12)

//@ref Parity_define
#define USART_Parity_NONE			(uint32_t)(0)
#define USART_Parity_EVEN       	(uint32_t)(1<<10)
#define USART_Parity_ODD			(uint32_t)(1<<10 | 1<<9)


//@ref StopBits_define
#define USART_StopBits_HALF			(uint32_t)(1<<12)
#define USART_StopBits_1			(uint32_t)(0)
#define USART_StopBits_1_HALF		(uint32_t)(3<<12)
#define USART_StopBits_2			(uint32_t)(2<<12)

//@ref FlowControl_define
#define FlowControl_NONE			(uint32_t)(0)
#define FlowControl_CTS				(uint32_t)(1<<9)
#define FlowControl_RTS				(uint32_t)(1<<8)
#define FlowControl_CTS_RTS			(uint32_t)(1<<9 | 1<<8)

//@ref IRQ_Enable_define
#define IRQ_Enable_NONE         	(uint32_t)(0)
#define IRQ_Enable_TXE				(uint32_t)(1<<7) // Transmit data register empty
#define IRQ_Enable_TC				(uint32_t)(1<<6) // Transmission complete
#define IRQ_Enable_RXNE				(uint32_t)(1<<5) // Received data ready to be read & Overrun error detected
#define IRQ_Enable_PE				(uint32_t)(1<<8) // Parity error

// Baud Rate Calculations
#define USARTDIV_MUL100(pclk, baudrate)		(uint32_t)((pclk * 25) / (4 * baudrate))
#define MANTISSA(pclk, baudrate)			(uint32_t)(USARTDIV_MUL100(pclk, baudrate) / 100)
#define FRACTION_MUL100(pclk, baudrate)		(uint32_t)(USARTDIV_MUL100(pclk, baudrate) % 100)
#define FRACTION(pclk, baudrate)			(uint32_t)(FRACTION_MUL100(pclk, baudrate) * 16 / 100)
#define USART_BRR_REG(pclk, baudrate)		(MANTISSA(pclk, baudrate) << 4) | (FRACTION(pclk, baudrate) & 0xF)

//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct
{
	uint8_t USART_Mode     ; // Specifies the Tx/Rx Mode.
							 // This parameter can be a value of @ref USART_Mode_define

	uint32_t BaudRate      ; // Specifies the USART communication baud rate for asynchronous operation
						     // This parameter can be a value of @ref BaudRate_define

	uint8_t Payload_Length ; // Specifies the number of data bits transmitted/received per frame
							 // This parameter can be a value of @ref Payload_Length_define

	uint8_t Parity         ; // Specifies the parity mode
							 // This parameter can be a value of @ref Parity_define

	uint8_t StopBits       ; // Specifies the number of stop bits transmitted
	 	 	 	 	 	 	 // This parameter can be a value of @ref StopBits_define

	uint8_t FlowControl    ; // Specifies whether the hardware flow control is enabled or not
	 	 	 	 	 	 	 // This parameter can be a value of @ref FlowControl_define

	uint8_t IRQ_Enable     ; // Specifies whether the USART IRQ TX/RX is enabled or not
	 	 	 	 	 	 	 // This parameter can be a value of @ref IRQ_Enable_define

	void (*P_IRQ_CallBack)(void); // Specifies the C function which will be called once the IRQ happen

}USART_Config_t;

/*
* ===============================================
* Generic Declaration
* ===============================================
*/
enum pollingmechanism
{
	enable,
	disable
};

/*
* ===============================================
* APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/
void MCAL_USART_Init(USART_TypeDef *USARTx, USART_Config_t *USARTConfig);
void MCAL_USART_DeInit(USART_TypeDef *USARTx );
void MCAL_USART_GPIO_Set_Pins(USART_TypeDef *USARTx);
void MCAL_USART_SendData(USART_TypeDef *USARTx, uint16_t *pTxbuffer, enum pollingmechanism pollingstate);
void MCAL_USART_ReceiveData(USART_TypeDef *USARTx, uint16_t *pRxbuffer, enum pollingmechanism pollingstate);
void MCAL_UART_WAIT_TC(USART_TypeDef *USARTx);

#endif /* STM32F103C6_USART_DRIVER_H_ */
