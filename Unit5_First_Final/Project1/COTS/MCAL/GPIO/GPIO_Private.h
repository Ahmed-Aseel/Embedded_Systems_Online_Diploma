/*
 * GPIO_Private.h
 *
 *  Created on: Aug 28, 2022
 *      Author: Ahmed Aseel
 */

/********** Header Protection **********/
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#define APB2ENR    *(volatile uint32_t *)(BASE_RCC   + 0x18)
#define GPIOA_CRL  *(volatile uint32_t *)(GPIO_PORTA + 0x00)
#define GPIOA_CRH  *(volatile uint32_t *)(GPIO_PORTA + 0X04)
#define GPIOA_IDR  *(volatile uint32_t *)(GPIO_PORTA + 0x08)
#define GPIOA_ODR  *(volatile uint32_t *)(GPIO_PORTA + 0x0C)

#endif /******** GPIO_PRIVATE_H_ ********/
