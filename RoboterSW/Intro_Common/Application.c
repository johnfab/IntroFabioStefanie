/*
 * Application.c
 *
 *  Created on: 28.02.2016
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "Event.h"
#include "LED.h"
#include "WAIT1.h"
#include "CS1.h"
#include "Keys.h"
#include "CLS1.h"
//#include "FRTOS1.h"

#if PL_CONFIG_HAS_EVENTS
static void APP_EventHandler(EVNT_Handle event) {
  switch(event) {
  case EVNT_STARTUP:
    LED1_On(); /* just do something */
    break;
  case EVNT_LED_HEARTBEAT:
    LED1_Neg();
    break;
#if PL_CONFIG_HAS_KEYS
  #if PL_CONFIG_NOF_KEYS>=1
  case EVNT_SW1_PRESSED:
    LED2_Neg();
    CLS1_SendStr("SW1 pressed\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT_SW1_LPRESSED:
	LED3_Neg();
	CLS1_SendStr("SW1 long pressed\r\n", CLS1_GetStdio()->stdOut);
	break;
 #endif
 #if PL_CONFIG_NOF_KEYS>=2
  case EVNT_SW2_PRESSED:
    LED2_Neg();
    CLS1_SendStr("SW2 pressed\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT_SW2_LPRESSED:
 	LED3_Neg();
 	CLS1_SendStr("SW2 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=3
  case EVNT_SW3_PRESSED:
    LED2_Neg();
    CLS1_SendStr("SW3 pressed\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT_SW3_LPRESSED:
 	LED3_Neg();
 	CLS1_SendStr("SW3 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=4
  case EVNT_SW4_PRESSED:
    LED2_Neg();
    CLS1_SendStr("SW4 pressed\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT_SW4_LPRESSED:
 	LED3_Neg();
 	CLS1_SendStr("SW4 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=5
  case EVNT_SW5_PRESSED:
    LED2_Neg();
    CLS1_SendStr("SW5 pressed\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT_SW5_LPRESSED:
 	LED3_Neg();
 	CLS1_SendStr("SW5 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=6
  case EVNT_SW6_PRESSED:
    LED2_Neg();
    CLS1_SendStr("SW6 pressed\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT_SW6_LPRESSED:
 	LED3_Neg();
 	CLS1_SendStr("SW6 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=7
  case EVNT_SW7_PRESSED:
    LED2_Neg();
    CLS1_SendStr("SW7 pressed\r\n", CLS1_GetStdio()->stdOut);
    break;
  case EVNT_SW7_LPRESSED:
 	LED3_Neg();
 	CLS1_SendStr("SW7 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	break;
  #endif
#endif
  } /* switch */
}
#endif /* PL_CONFIG_HAS_EVENTS */

void APP_Start(void) {
  PL_Init();
  //vTaskStartScheduler();
#if PL_CONFIG_HAS_EVENTS
  EVNT_SetEvent(EVNT_STARTUP);
#endif
  CLS1_SendStr("Hello World!\r\n", CLS1_GetStdio()->stdOut);

  Cpu_EnableInt();

  for(;;) {
#if PL_CONFIG_HAS_KEYS
    KEY_Scan();
#endif
#if PL_CONFIG_HAS_EVENTS
    EVNT_HandleEvent(APP_EventHandler, TRUE);
#endif
    WAIT1_Waitms(25); /* just wait for some arbitrary time .... */
  }
}


