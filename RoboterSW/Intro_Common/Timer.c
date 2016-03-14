/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for all our timers.
  */

#include "Platform.h"
#if PL_CONFIG_HAS_TIMER
#include "Timer.h"
#include "Event.h"

void TMR_OnInterrupt(void) {
  /* this one gets called from an interrupt!!!! */
  /*! \todo Add code for a blinking LED here */
}

void TMR_Init(void) {
}

void TMR_Deinit(void) {
}

#endif /*PL_HAS_TIMER*/
