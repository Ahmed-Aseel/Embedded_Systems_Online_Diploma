/*
 * STM32F103x6.h
 *
 *  Created on: Sep 18, 2022
 *      Author: Ahmed Aseel
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------
#include <stdlib.h>
#include <stdint.h>

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BASE						0x08000000UL
#define SYSTEM_MEMORY_BASE						0x1FFFF000UL
#define SRAM_MEMORY_BASE						0x20000000UL
#define PERIPHERALS_BASE						0x40000000UL
#define CORTEXM3_INTERNAL_PERIPHERALS_BASE		0xE0000000UL
//NVIC register map
#define NVIC_BASE								0xE000E100UL
#define NVIC_ISER0								*(volatile uint32_t*)(NVIC_BASE + 0x000)
#define NVIC_ISER1								*(volatile uint32_t*)(NVIC_BASE + 0x004)
#define NVIC_ISER2								*(volatile uint32_t*)(NVIC_BASE + 0x008)
#define NVIC_ICER0								*(volatile uint32_t*)(NVIC_BASE + 0x080)
#define NVIC_ICER1								*(volatile uint32_t*)(NVIC_BASE + 0x084)
#define NVIC_ICER2								*(volatile uint32_t*)(NVIC_BASE + 0x088)

//-----------------------------
//Base addresses for AHB BUS Peripherals
//-----------------------------
//RCC
#define RCC_BASE								0x40021000UL

//-----------------------------
//Base addresses for APB2 BUS Peripherals
//-----------------------------
//AFIO
#define AFIO_BASE								0x40010000UL

//EXTI
#define EXTI_BASE								0x40010400UL

//GPIO
//A,B are fully included in LQFP48 package
#define GPIOA_BASE								0x40010800UL
#define GPIOB_BASE								0x40010C00UL

//C,D are partially included in LQFP48 package
#define GPIOC_BASE								0x40011000UL
#define GPIOD_BASE								0x40011400UL

//E is not included in LQFP48 package
#define GPIOE_BASE								0x40011800UL

//-----------------------------
//Base addresses for APB1 BUS Peripherals
//-----------------------------


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t EVCR     ;
	volatile uint32_t MAPR     ;
	volatile uint32_t EXTICR[4];
//	volatile uint32_t EXTICR1  ;
//	volatile uint32_t EXTICR2  ;
//	volatile uint32_t EXTICR3  ;
//	volatile uint32_t EXTICR4  ;
	volatile uint32_t RESERVED ; // 0x18
	volatile uint32_t MAPR2    ; // 0x1C

}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t IMR   ;
	volatile uint32_t EMR   ;
	volatile uint32_t RTSR  ;
	volatile uint32_t FTSR  ;
	volatile uint32_t SWIER ;
	volatile uint32_t PR    ;

}EXTI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR       ;
	volatile uint32_t CFGR     ;
	volatile uint32_t CIR      ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR ;
	volatile uint32_t AHBENR   ;
	volatile uint32_t APB2ENR  ;
	volatile uint32_t APB1ENR  ;
	volatile uint32_t BDCR     ;
	volatile uint32_t CSR      ;
	volatile uint32_t AHBSTR   ;
	volatile uint32_t CFGR2    ;

}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL  ;
	volatile uint32_t CRH  ;
	volatile uint32_t IDR  ;
	volatile uint32_t ODR  ;
	volatile uint32_t BSRR ;
	volatile uint32_t BRR  ;
	volatile uint32_t LCKR ;

}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA		((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB		((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC    	((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD    	((GPIO_TypeDef*) GPIOD_BASE)
#define GPIOE    	((GPIO_TypeDef*) GPIOE_BASE)

#define RCC    		((RCC_TypeDef*) RCC_BASE)

#define EXTI    	((EXTI_TypeDef*) EXTI_BASE)

#define AFIO    	((AFIO_TypeDef*) AFIO_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC_AFIO_CLK_EN()		(RCC->APB2ENR |= (1<<0))
#define RCC_GPIOA_CLK_EN()		(RCC->APB2ENR |= (1<<2))
#define RCC_GPIOB_CLK_EN()		(RCC->APB2ENR |= (1<<3))
#define RCC_GPIOC_CLK_EN()		(RCC->APB2ENR |= (1<<4))
#define RCC_GPIOD_CLK_EN()		(RCC->APB2ENR |= (1<<5))
#define RCC_GPIOE_CLK_EN()		(RCC->APB2ENR |= (1<<6))

//-*-*-*-*-*-*-*-*-*-*-*-
//IVT:
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI
#define EXTI0_IRQ			6
#define EXTI1_IRQ			7
#define EXTI2_IRQ			8
#define EXTI3_IRQ			9
#define EXTI4_IRQ			10
#define EXTI5_IRQ			23
#define EXTI6_IRQ			23
#define EXTI7_IRQ			23
#define EXTI8_IRQ			23
#define EXTI9_IRQ			23
#define EXTI10_IRQ			40
#define EXTI11_IRQ			40
#define EXTI12_IRQ			40
#define EXTI13_IRQ			40
#define EXTI14_IRQ			40
#define EXTI15_IRQ			40

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ Enable/Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#define NVIC_IRQ6_EXTI0_Enable()				(NVIC_ISER0 |= (1<<6))
#define NVIC_IRQ7_EXTI1_Enable()				(NVIC_ISER0 |= (1<<7))
#define NVIC_IRQ8_EXTI2_Enable()				(NVIC_ISER0 |= (1<<8))
#define NVIC_IRQ9_EXTI3_Enable()				(NVIC_ISER0 |= (1<<9))
#define NVIC_IRQ10_EXTI4_Enable()				(NVIC_ISER0 |= (1<<10))
#define NVIC_IRQ23_EXTI9_5_Enable()				(NVIC_ISER0 |= (1<<23))
#define NVIC_IRQ40_EXTI15_10_Enable()			(NVIC_ISER1 |= (1<<8)) // 40-32 = 8

#define NVIC_IRQ6_EXTI0_Disable()				(NVIC_ICER0 |= (1<<6))
#define NVIC_IRQ7_EXTI1_Disable()				(NVIC_ICER0 |= (1<<7))
#define NVIC_IRQ8_EXTI2_Disable()				(NVIC_ICER0 |= (1<<8))
#define NVIC_IRQ9_EXTI3_Disable()				(NVIC_ICER0 |= (1<<9))
#define NVIC_IRQ10_EXTI4_Disable()				(NVIC_ICER0 |= (1<<10))
#define NVIC_IRQ23_EXTI9_5_Disable()			(NVIC_ICER0 |= (1<<23))
#define NVIC_IRQ40_EXTI15_10_Disable()			(NVIC_ICER1 |= (1<<8)) // 40-32 = 8

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#endif /* INC_STM32F103X6_H_ */
