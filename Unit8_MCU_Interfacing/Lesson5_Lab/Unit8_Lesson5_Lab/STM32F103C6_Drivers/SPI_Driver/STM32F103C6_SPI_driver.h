/*
 * STM32F103C6_SPI_driver.h
 *
 *  Created on: Feb 17, 2023
 *      Author: Ahmed Aseel
 */

#ifndef SPI_DRIVER_STM32F103C6_SPI_DRIVER_H_
#define SPI_DRIVER_STM32F103C6_SPI_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref Device_Mode_define
#define SPI_Device_Mode_SLAVE					(uint16_t)(0)
#define SPI_Device_Mode_MASTER					(uint16_t)(1<<2) //CR1 Bit 2 MSTR: Master selection

//@ref Communication_Mode_define
#define SPI_Direction_2Lines					(uint16_t)(0)
#define SPI_Direction_2Lines_RXonly				(uint16_t)(1<<10) //CR1 Bit 10 RXONLY: Receive only
#define SPI_Direction_1Lines_RXonly				(uint16_t)(1<<15) //CR1 Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_Direction_1Lines_TXonly				(uint16_t)(1<<15 | 1<<14) //CR1 Bit 14 BIDIOE: Output enable in bidirectional mode

//@ref Frame_Formate_define
#define SPI_Frame_Formate_MSB_FIRST				(uint16_t)(0)
#define SPI_Frame_Formate_LSB_FIRST				(uint16_t)(1<<7) //CR1 Bit 7 LSBFIRST: Frame format

//@ref Data_Size_define
#define SPI_Data_Size_8B						(uint16_t)(0)
#define SPI_Data_Size_16B						(uint16_t)(1<<11) //CR1 Bit 11 DFF: Data frame format

//@ref CLK_Polarity_define
#define SPI_CLK_Polarity_Idle_Low				(uint16_t)(0)
#define SPI_CLK_Polarity_Idle_High				(uint16_t)(1<<1) //CR1 Bit1 CPOL: Clock polarity

//@ref CLK_Phase_define
#define SPI_CLK_Phase_FirstEdge_Capturedata		(uint16_t)(0)
#define SPI_CLK_Phase_SecondEdge_Capturedata	(uint16_t)(1<<0) //CR1 Bit 0 CPHA: Clock phase

//@ref SPI_NSS_define
// Hardware
#define SPI_NSS_Hard_Slave						(uint16_t)(0)
#define SPI_NSS_Hard_MASTER_SS_Output_Enable	(uint16_t)(1<<2) //CR2 Bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_MASTER_SS_Output_Disable  ~(uint16_t)(1<<2) //CR2 Bit 2 SSOE: SS output enable

// NSS is driven by Software (Master/Slave)
#define SPI_NSS_Soft_NSSInternalSoft_Reset		(uint16_t)(1<<9)        //CR1 Bit 9 SSM: Software slave management
#define SPI_NSS_Soft_NSSInternalSoft_Set		(uint16_t)(1<<9 | 1<<8) //CR1 Bit 8 SSI: Internal slave select

//@ref BaudRate_Control_define
#define SPI_BaudRate_PreScaler_2				(uint16_t)(0b000<<3)
#define SPI_BaudRate_PreScaler_4				(uint16_t)(0b001<<3)
#define SPI_BaudRate_PreScaler_8				(uint16_t)(0b010<<3)
#define SPI_BaudRate_PreScaler_16				(uint16_t)(0b011<<3)
#define SPI_BaudRate_PreScaler_32				(uint16_t)(0b100<<3)
#define SPI_BaudRate_PreScaler_64				(uint16_t)(0b101<<3)
#define SPI_BaudRate_PreScaler_128				(uint16_t)(0b110<<3)
#define SPI_BaudRate_PreScaler_256				(uint16_t)(0b111<<3)

//@ref IRQ_Enable_define
#define SPI_IRQ_Enable_NONE         			(uint32_t)(0)
#define SPI_IRQ_Enable_TXE						(uint32_t)(1<<7) //CR2 Bit7 TXEIE: Transmit data register empty
#define SPI_IRQ_Enable_RXNE						(uint32_t)(1<<6) //CR2 Bit6 RXNEIE: Received data ready to be read & Overrun error detected
#define SPI_IRQ_Enable_ERRI						(uint32_t)(1<<5) //CR2 Bit5 ERRIE: Error interrupt enable

//-----------------------------
//User type definitions (structures)
//-----------------------------

struct S_IRQ_SRC
{
	uint8_t TXE:1;
	uint8_t RXNE:1;
	uint8_t ERRI:1;
	uint8_t Reserved:5;
};

typedef struct
{
	uint16_t Device_Mode       ; // Specifies the SPI operating mode.
							     // This parameter can be a value of @ref Device_Mode_define

	uint16_t Communication_Mode; // Specifies the SPI bidirectional mode.
								 // This parameter can be a value of @ref Communication_Mode_define

	uint16_t Frame_Formate     ; // Specifies LSB or MSB first
								 // This parameter can be a value of @ref Frame_Formate_define

	uint16_t Data_Size         ; // Specifies the size of the data to be transmitted/received
	 	 	 	 	 	 	 	 // This parameter can be a value of @ref Data_Size_define

	uint16_t CLK_Polarity      ; // Specifies the idle clock level
	 	 	 	 	 	 	 	 // This parameter can be a value of @ref CLK_Polarity_define

	uint16_t CLK_Phase         ; // Specifies the first data capture edge
	 	 	 	 	 	 	 	 // This parameter can be a value of @ref CLK_Phase_define

	uint16_t NSS               ; // Specifies//Specifies whether the NSS signal is managed by
								 // hardware(NSS pin)or by software using the SSI bit enable or disable
	 	 	 	 	 	 	 	 // This parameter can be a value of @ref SPI_NSS_define

	uint16_t BaudRate_Control  ; // Specifies the Baud Rate prescaler value which will be used to
								 // Configure the transmit and receive SCK clock. This parameter
								 // @note The communication clock is derived from the master clock.
	                             // The slave clock does not need to be set.
	 	 	 	 	 	 	 	 // This parameter can be a value of @ref BaudRate_Control_define

	uint8_t IRQ_Enable         ; // Specifies whether the SPI IRQ TX/RX is enabled or not
	 	 	 	 	 	 	     // This parameter can be a value of @ref IRQ_Enable_define

	void (*P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);// Specifies the C function which will be called once the IRQ happen

}SPI_Config_t;

/*
* ===============================================
* Generic Declaration
* ===============================================
*/
enum polling_mechanism
{
	polling_enable,
	polling_disable
};

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void MCAL_SPI_Init(SPI_TypeDef *SPIx, SPI_Config_t *SPIConfig);
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx );
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx);
void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTxbuffer, enum polling_mechanism pollingstate);
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pRxbuffer, enum polling_mechanism pollingstate);
void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t *pBuffer, enum polling_mechanism pollingstate);

#endif /* SPI_DRIVER_STM32F103C6_SPI_DRIVER_H_ */
