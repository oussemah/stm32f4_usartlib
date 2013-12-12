/* File : main.c
 * Desc : demo of the stm32f4_libusart library
 * Auth : Oussema HARBI oussema.elharbi@gmail.com
 */

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>

/* I use a special implmentation of printf through USARt port */
#include <stdio.h>

#include "libUSART.h"

/* A sample delay function */
inline void delay_ms(__IO uint32_t ms)
{
	ms *= 1300; /* This value was calculated by EXPERIENCE, no theoretical rules behind this so far */
	while(ms--) {
		__NOP();
	}
}

int main(void)
{
	uint32_t number = 0;

	 /* Set unbuffered mode for stdout (newlib) */
	setvbuf( stdout, 0, _IONBF, 0 );

        /* Inizialize USART_DEBUG port with a speed of 115200 bauds */
	USARTInit( USART_DEBUG, 115200);

    while(1)
    {
    	delay_ms(1000);
    	printf("Num : %d \r\n", number);
    	number *= 2;
    }

    return 0;
}

