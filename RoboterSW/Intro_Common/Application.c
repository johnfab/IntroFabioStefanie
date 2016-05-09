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
#if PL_CONFIG_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_CONFIG_HAS_RTOS
  #include "FRTOS1.h"
  #include "RTOS.h"
#endif
#if PL_CONFIG_HAS_SHELL
  #include "Shell.h"
#endif

#if PL_CONFIG_HAS_EVENTS
static void APP_EventHandler(EVNT_Handle event) {
  switch(event) {
  case EVNT_STARTUP:
    LED1_On(); /* just do something */
#if PL_CONFIG_HAS_BUZZER
    BUZ_PlayTune(BUZ_TUNE_WELCOME);
#endif
    break;
  case EVNT_LED_HEARTBEAT:
    LED1_Neg();
    break;
#if PL_CONFIG_HAS_KEYS
  #if PL_CONFIG_NOF_KEYS>=1
  case EVNT_SW1_PRESSED:
    LED2_Neg();
	SHELL_SendString("SW1 pressed\r\n");
#if PL_CONFIG_HAS_BUZZER
    BUZ_PlayTune(BUZ_TUNE_BUTTON);
#endif
	break;
  case EVNT_SW1_RELEASED:
    SHELL_SendString("SW1 released\r\n");
    break;
  case EVNT_SW1_LPRESSED:
	LED2_Off();
	//CLS1_SendStr("SW1 long pressed\r\n", CLS1_GetStdio()->stdOut);
	SHELL_SendString("SW1 long pressed\r\n");
#if PL_CONFIG_HAS_BUZZER
    BUZ_PlayTune(BUZ_TUNE_BUTTON_LONG);
#endif
	break;
 #endif
 #if PL_CONFIG_NOF_KEYS>=2
  case EVNT_SW2_PRESSED:
    LED2_Neg();
    //CLS1_SendStr("SW2 pressed\r\n", CLS1_GetStdio()->stdOut);
	SHELL_SendString("SW2 pressed\r\n");
    break;
  case EVNT_SW2_LPRESSED:
 	LED2_Neg();
 	//CLS1_SendStr("SW2 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	SHELL_SendString("SW2 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=3
  case EVNT_SW3_PRESSED:
    LED2_Neg();
    //CLS1_SendStr("SW3 pressed\r\n", CLS1_GetStdio()->stdOut);
    SHELL_SendString("SW3 pressed\r\n");
    break;
  case EVNT_SW3_LPRESSED:
 	LED2_Neg();
 	//CLS1_SendStr("SW3 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	SHELL_SendString("SW3 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=4
  case EVNT_SW4_PRESSED:
    LED2_Neg();
    //CLS1_SendStr("SW4 pressed\r\n", CLS1_GetStdio()->stdOut);
    SHELL_SendString("SW4 pressed\r\n");
    break;
  case EVNT_SW4_LPRESSED:
 	LED2_Neg();
 	//CLS1_SendStr("SW4 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	SHELL_SendString("SW4 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=5
  case EVNT_SW5_PRESSED:
    LED2_Neg();
    //CLS1_SendStr("SW5 pressed\r\n", CLS1_GetStdio()->stdOut);
    SHELL_SendString("SW5 pressed\r\n");
    break;
  case EVNT_SW5_LPRESSED:
 	LED2_Neg();
 	//CLS1_SendStr("SW5 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	SHELL_SendString("SW5 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=6
  case EVNT_SW6_PRESSED:
    LED2_Neg();
    //CLS1_SendStr("SW6 pressed\r\n", CLS1_GetStdio()->stdOut);
    SHELL_SendString("SW6 pressed\r\n");
    break;
  case EVNT_SW6_LPRESSED:
 	LED2_Neg();
 	//CLS1_SendStr("SW6 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	SHELL_SendString("SW6 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=7
  case EVNT_SW7_PRESSED:
    LED2_Neg();
    //CLS1_SendStr("SW7 pressed\r\n", CLS1_GetStdio()->stdOut);
    SHELL_SendString("SW7 pressed\r\n");
    break;
  case EVNT_SW7_LPRESSED:
 	LED2_Neg();
 	//CLS1_SendStr("SW7 long pressed\r\n", CLS1_GetStdio()->stdOut);
 	SHELL_SendString("SW7 long pressed\r\n");
 	break;
  #endif
#endif
  } /* switch */
}
#endif /* PL_CONFIG_HAS_EVENTS */

/* Fallback Code if RTOS fails */
void APP_Start(void) {
  PL_Init();
  //vTaskStartScheduler();
#if PL_CONFIG_HAS_EVENTS
  EVNT_SetEvent(EVNT_STARTUP);
#endif
#if CLS1_DEFAULT_SERIAL
  CLS1_SendStr("Hello World!\r\n", CLS1_GetStdio()->stdOut);
#endif
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


