/* File : libUSART.c
 * Desc : Implementing the stm32f4_libusart library
 * Auth : Oussema HARBI oussema.elharbi@gmail.com
 */

#include "libUSART.h"


inline GPIO_TypeDef* USART2GPIO(USART_TypeDef* periph)
{
	if (periph == USART1) {
		return GPIOA;
	}
	if (periph == USART2) {
		return GPIOD;
	}
	if (periph == USART3) {
		return GPIOC;
	}
	else {
		return GPIOD;
	}
}

inline uint32_t RX(USART_TypeDef* periph)
{
	if (periph == USART1) {
		return GPIO_Pin_10;
	}
	if (periph == USART2) {
		return GPIO_Pin_6;
	}
	if (periph == USART3) {
		return GPIO_Pin_11;
	}
	return 0;
}

inline uint32_t TX(USART_TypeDef* periph)
{
	if (periph == USART1) {
		return GPIO_Pin_9;
	}
	if (periph == USART2) {
		return GPIO_Pin_5;
	}
	if (periph == USART3) {
		return GPIO_Pin_10;
	}
	return 0;
}

#define TX_Func 0
#define RX_Func 1

inline uint16_t PinAF_USART(USART_TypeDef* periph, uint8_t USART_Function)
{
	if (periph == USART1) {
		if (USART_Function == TX_Func)
			return GPIO_PinSource9;
		else {
			return GPIO_PinSource10;
		}
	}
	if (periph == USART2) {
		if (USART_Function == TX_Func)
			return GPIO_PinSource5;
		else {
			return GPIO_PinSource6;
		}
	}
	if (periph == USART3) {
		if (USART_Function == TX_Func)
			return GPIO_PinSource10;
		else {
			return GPIO_PinSource11;
		}
	}
	return 0;
}

inline uint8_t ModeAF_USART(USART_TypeDef* periph)
{
	if (periph == USART1) {
		return GPIO_AF_USART1;
	}
	if (periph == USART2) {
		return GPIO_AF_USART2;
	}
	if (periph == USART3) {
		return GPIO_AF_USART3;
	}
	return 0;
}

inline uint32_t USARTCLOCK(USART_TypeDef* periph)
{
	if (periph == USART1) {
		return RCC_APB2Periph_USART1;
	}
	if (periph == USART2) {
		return RCC_APB1Periph_USART2;
	}
	if (periph == USART3) {
		return RCC_APB1Periph_USART3;
	}
	return 0;
}

inline uint32_t PORTCLOCK(GPIO_TypeDef* periph)
{
	if (periph == GPIOA) {
		return RCC_AHB1Periph_GPIOA;
	}
	if (periph == GPIOB) {
		return RCC_AHB1Periph_GPIOB;
	}
	if (periph == GPIOC) {
		return RCC_AHB1Periph_GPIOC;
	}
	if (periph == GPIOD) {
		return RCC_AHB1Periph_GPIOD;
	}
	return 0;
}

void USARTInit( USART_TypeDef* periph, uint32_t speed)
{
  /* USARTx configured as follow:
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */

  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd( PORTCLOCK(USART2GPIO(periph)), ENABLE);

  /* Enable UART clock */
  RCC_APB1PeriphClockCmd( USARTCLOCK(periph), ENABLE); //

  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig( USART2GPIO(periph), PinAF_USART( periph, TX_Func), ModeAF_USART(periph));

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig( USART2GPIO(periph), PinAF_USART( periph, RX_Func), ModeAF_USART(periph));

  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = TX(periph);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( USART2GPIO(periph), &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = RX(periph);
  GPIO_Init( USART2GPIO(periph), &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = speed;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* USART configuration */
  USART_Init( periph, &USART_InitStructure);

  /* Enable USART */
  USART_Cmd( periph, ENABLE);

}
