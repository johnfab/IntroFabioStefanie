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
#include "Trigger.h"

void TMR_OnInterrupt(void) {
  /* this one gets called from an interrupt!!!! */
  /*! \todo Add code for a blinking LED here */
  static unsigned int cntr = 0;
  #define BLINK_PERIOD_MS 1000
  /* this one gets called from an interrupt!!!! */
  cntr++;
  if ((cntr%(BLINK_PERIOD_MS/TMR_TICK_MS))==0) { /* every two seconds */
    EVNT_SetEvent(EVNT_LED_HEARTBEAT);
  }

  /* Add a tick to the Trigger Handling */
#if PL_CONFIG_HAS_TRIGGER
  TRG_AddTick();
#endif

}

void TMR_Init(void) {
}

void TMR_Deinit(void) {
}

#endif /* PL_CONFIG_HAS_TIMER*/
