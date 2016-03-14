/*
 * Platform.c
 *
 *  Created on: 28.02.2016
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_CONFIG_HAS_LEDS
  #include "LED.h"
#endif
#if PL_CONFIG_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_CONFIG_HAS_TIMER
  #include "Timer.h"
#endif
#if PL_CONFIG_HAS_KEYS
  #include "Keys.h"
#endif

void PL_Init(void) {
#if PL_CONFIG_HAS_LEDS
  LED_Init();
#endif
#if PL_CONFIG_HAS_EVENTS
  EVNT_Init();
#endif
#if PL_CONFIG_HAS_TIMER
  TMR_Init();
#endif
#if PL_CONFIG_HAS_KEYS
  KEY_Init();
#endif
}

void PL_Deinit(void) {
#if PL_CONFIG_HAS_KEYS
  KEY_Deinit();
#endif
#if PL_CONFIG_HAS_TIMER
  TMR_Deinit();
#endif
#if PL_CONFIG_HAS_EVENTS
  EVNT_Init();
#endif
#if PL_CONFIG_HAS_LEDS
  LED_Deinit();
#endif
}


