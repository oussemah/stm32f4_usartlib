/* File : libUSART.h
 * Desc : Header of the stm32f4_libusart library
 * Auth : Oussema HARBI oussema.elharbi@gmail.com
 */

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

#define USART_DEBUG USART3

void USARTInit(USART_TypeDef* periph, uint32_t speed);

