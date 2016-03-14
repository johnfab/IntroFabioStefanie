/*
 * Application.c
 *
 *  Created on: 28.02.2016
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "LED.h"
#include "WAIT1.h"
#include "CS1.h"

void APP_Start(void) {
  CS1_CriticalVariable();

  PL_Init();
  /* init: turn off */
  for(;;) {
   // CS1_EnterCritical();
    LED1_Neg();
    //CS1_ExitCritical();
    WAIT1_Waitms(500);
  }

  for(;;) {
    /* wait */
  }
}


