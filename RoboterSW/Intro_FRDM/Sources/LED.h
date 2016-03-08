/*
 * LED.h
 * LED Treiber
 *  Created on: 01.03.2016
 *      Author: fabio
 */

#ifndef SOURCES_LED_H_
#define SOURCES_LED_H_

#if PL_NOF_LED >= 1
	#include "LEDpin1.h"
#endif

#define LED_TURN_ON(nr)  (LEDpin##nr##_ClrVal())
// ---> umschreiben auf LEDpin


#define LED1_On(void) (LED_TURN_ON(1))
#define LED1_Off(void)
#define LED1_Neg(void)
#define LED1_Get(void)
#define LED1_Put(bool)
#define LED1_Open(void)
#define LED1_Close(void)
#define LED1_Init(void)
#define LED1_Deinit(void)

#endif /* SOURCES_LED_H_ */
