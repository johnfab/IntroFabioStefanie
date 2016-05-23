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
#if PL_CONFIG_HAS_LINE_FOLLOW
	#include "LineFollow.h"
#endif
#if PL_CONFIG_HAS_REFLECTANCE
  #include "Reflectance.h"
#endif

#if PL_CONFIG_HAS_REMOTE
	#include "RApp.h"
	#include "RNet_App.h"
	#include "RNet_AppConfig.h"
	#include "Remote.h"
#endif

static uint8_t buf;
static RNWK_ShortAddrType commPartnerAddress;

#if PL_CONFIG_HAS_EVENTS
void APP_EventHandler(EVNT_Handle event) {

  switch(event) {
  case EVNT_STARTUP:
    LED1_On(); /* just do something */
    commPartnerAddress = RNETA_GetDestAddr();
#if PL_CONFIG_HAS_BUZZER
    BUZ_PlayTune(BUZ_TUNE_WELCOME);
#endif
    break;
  case EVNT_LED_HEARTBEAT:
    LED1_Neg();
    break;

#if PL_CONFIG_HAS_KEYS
  #if PL_CONFIG_NOF_KEYS>=1
    // Button 1 (A) ----------------------------------------------------------------------
  case EVNT_SW1_PRESSED:
    LED2_Neg();
	SHELL_SendString("SW1 pressed\r\n");
	#if PL_CONFIG_HAS_BUZZER
	    BUZ_PlayTune(BUZ_TUNE_BUTTON);
	#endif
	#if PL_CONFIG_BOARD_IS_ROBO
	    // What should the robot do on a short press
	    #if PL_CONFIG_HAS_LINE_FOLLOW
	    	LF_StartStopFollowing();
	    #endif
	#endif
	#if PL_CONFIG_BOARD_IS_FRDM && PL_CONFIG_HAS_REMOTE
	    	buf = 'A';
	    	(void) RAPP_SendPayloadDataBlock(&buf, sizeof(buf), RAPP_MSG_TYPE_JOYSTICK_BTN, commPartnerAddress, RPHY_PACKET_FLAGS_REQ_ACK);
	#endif
	break;
  case EVNT_SW1_RELEASED:
    break;
  case EVNT_SW1_LPRESSED:
	LED2_Off();
	SHELL_SendString("SW1 long pressed\r\n");
	#if PL_CONFIG_HAS_BUZZER
    	BUZ_PlayTune(BUZ_TUNE_BUTTON_LONG);
	#endif
	#if PL_CONFIG_BOARD_IS_ROBO
	    // What should the robot do on a long press
	    #if PL_CONFIG_HAS_LINE_FOLLOW
	    	REF_CalibrateStartStop();
	    #endif
	#endif
	break;
 #endif
 #if PL_CONFIG_NOF_KEYS>=2
	// Button 2 (B) ----------------------------------------------------------------------
  case EVNT_SW2_PRESSED:
	SHELL_SendString("SW2 pressed\r\n");
	#if PL_CONFIG_BOARD_IS_FRDM && PL_CONFIG_HAS_REMOTE
	    	buf = 'B';
	    	(void) RAPP_SendPayloadDataBlock(&buf, sizeof(buf), RAPP_MSG_TYPE_JOYSTICK_BTN, commPartnerAddress, RPHY_PACKET_FLAGS_REQ_ACK);
	#endif
    break;
  case EVNT_SW2_RELEASED:
    break;
  case EVNT_SW2_LPRESSED:
 	SHELL_SendString("SW2 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=3
 	// Button 3 (C) ----------------------------------------------------------------------
  case EVNT_SW3_PRESSED:
    SHELL_SendString("SW3 pressed\r\n");
	#if PL_CONFIG_BOARD_IS_FRDM && PL_CONFIG_HAS_REMOTE
	    	buf = 'C';
	    	(void) RAPP_SendPayloadDataBlock(&buf, sizeof(buf), RAPP_MSG_TYPE_JOYSTICK_BTN, commPartnerAddress, RPHY_PACKET_FLAGS_REQ_ACK);
	#endif
    break;
  case EVNT_SW3_RELEASED:
      break;
  case EVNT_SW3_LPRESSED:
 	SHELL_SendString("SW3 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=4
 	// Button 4 (D) ----------------------------------------------------------------------
  case EVNT_SW4_PRESSED:
    SHELL_SendString("SW4 pressed\r\n");
	#if PL_CONFIG_BOARD_IS_FRDM && PL_CONFIG_HAS_REMOTE
	    	buf = 'D';
	    	(void) RAPP_SendPayloadDataBlock(&buf, sizeof(buf), RAPP_MSG_TYPE_JOYSTICK_BTN, commPartnerAddress, RPHY_PACKET_FLAGS_REQ_ACK);
	#endif
    break;
  case EVNT_SW4_RELEASED:
      break;
  case EVNT_SW4_LPRESSED:
 	SHELL_SendString("SW4 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=5
 	// Button 5 (E) ----------------------------------------------------------------------
  case EVNT_SW5_PRESSED:
    SHELL_SendString("SW5 pressed\r\n");
	#if PL_CONFIG_BOARD_IS_FRDM && PL_CONFIG_HAS_REMOTE
    		if (REMOTE_GetOnOff()) {
    			REMOTE_SetOnOff(FALSE);
    		} else {
    			REMOTE_SetOnOff(TRUE);
    		}
	    	buf = 'E';
	    	(void) RAPP_SendPayloadDataBlock(&buf, sizeof(buf), RAPP_MSG_TYPE_JOYSTICK_BTN, commPartnerAddress, RPHY_PACKET_FLAGS_REQ_ACK);
	#endif
    break;
  case EVNT_SW5_RELEASED:
      break;
  case EVNT_SW5_LPRESSED:
 	SHELL_SendString("SW5 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=6
 	// Button 6 (F) ----------------------------------------------------------------------
  case EVNT_SW6_PRESSED:
    SHELL_SendString("SW6 pressed\r\n");
	#if PL_CONFIG_BOARD_IS_FRDM && PL_CONFIG_HAS_REMOTE
	    	buf = 'F';
	    	(void) RAPP_SendPayloadDataBlock(&buf, sizeof(buf), RAPP_MSG_TYPE_JOYSTICK_BTN, commPartnerAddress, RPHY_PACKET_FLAGS_REQ_ACK);
	#endif
    break;
  case EVNT_SW6_RELEASED:
      break;
  case EVNT_SW6_LPRESSED:
 	SHELL_SendString("SW6 long pressed\r\n");
 	break;
  #endif
  #if PL_CONFIG_NOF_KEYS>=7
 	// Button 7 (Joystick) ---------------------------------------------------------------
  case EVNT_SW7_PRESSED:
    SHELL_SendString("SW7 pressed\r\n");
	#if PL_CONFIG_BOARD_IS_FRDM && PL_CONFIG_HAS_REMOTE
	    	buf = 'G';
	    	(void) RAPP_SendPayloadDataBlock(&buf, sizeof(buf), RAPP_MSG_TYPE_JOYSTICK_BTN, commPartnerAddress, RPHY_PACKET_FLAGS_REQ_ACK);
	#endif
    break;
  case EVNT_SW7_RELEASED:
      break;
  case EVNT_SW7_LPRESSED:
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


