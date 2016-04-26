/*
 * Platform.h
 *
 *  Created on: 28.02.2016
 *      Author: Erich Styger
 */

#ifndef SOURCES_INTRO_COMMON_PLATFORM_H_
#define SOURCES_INTRO_COMMON_PLATFORM_H_

#include <stdint.h> /* types as uint8_t used in project */
#include <stdbool.h> /* for bool type */
#include "PE_Types.h" /* common Processor Expert types: bool, NULL, ... */
#include "Platform_Local.h" /* local project configuration, present in each project (FRDM, Robot) */
#include "Cpu.h" /* for PEcfg_RoboV2/PEcfg_RoboV1 */

/* check local platform configuration */
#if PL_LOCAL_CONFIG_BOARD_IS_ROBO
  #define PL_CONFIG_BOARD_IS_FRDM   (0)
  #define PL_CONFIG_BOARD_IS_ROBO   (1)
  #if defined(PEcfg_RoboV2)
    #define PL_CONFIG_BOARD_IS_ROBO_V1          (0)
    #define PL_CONFIG_BOARD_IS_ROBO_V2          (1)
  #else
    #define PL_CONFIG_BOARD_IS_ROBO_V1          (1)
    #define PL_CONFIG_BOARD_IS_ROBO_V2          (0)
  #endif
#elif PL_LOCAL_CONFIG_BOARD_IS_FRDM
  #define PL_CONFIG_BOARD_IS_FRDM   (1)
  #define PL_CONFIG_BOARD_IS_ROBO   (0)
#else
  #error "One board type has to be defined in Platform_Local.h!"
#endif


#define PL_CONFIG_TEST_DRIVERS  (1) /* if enabled, will perform driver tests */

/* configuration from local config */
#define PL_CONFIG_NOF_LEDS      PL_LOCAL_CONFIG_NOF_LEDS /* number of LEDs */
#define PL_CONFIG_NOF_KEYS      PL_LOCAL_CONFIG_NOF_KEYS /* number of keys */
#define PL_CONFIG_KEY_1_ISR     PL_LOCAL_CONFIG_KEY_1_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_2_ISR     PL_LOCAL_CONFIG_KEY_2_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_3_ISR     PL_LOCAL_CONFIG_KEY_3_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_4_ISR     PL_LOCAL_CONFIG_KEY_4_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_5_ISR     PL_LOCAL_CONFIG_KEY_5_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_6_ISR     PL_LOCAL_CONFIG_KEY_6_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_7_ISR     PL_LOCAL_CONFIG_KEY_7_ISR /* if key is using interrupt */
#define PL_CONFIG_HAS_KBI       (PL_CONFIG_KEY_1_ISR||PL_CONFIG_KEY_2_ISR||PL_CONFIG_KEY_3_ISR||PL_CONFIG_KEY_4_ISR||PL_CONFIG_KEY_5_ISR||PL_CONFIG_KEY_6_ISR||PL_CONFIG_KEY_7_ISR)

/* driver configuration */
#define PL_CONFIG_HAS_LEDS      (1 && !defined(PL_LOCAL_CONFIG_HAS_LEDS_DISABLED)) /* LED driver */
#define PL_CONFIG_HAS_EVENTS    (1) /* event driver */
#define PL_CONFIG_HAS_TIMER     (1) /* timer interrupts */
#define PL_CONFIG_HAS_KEYS      (1) /* support for keys */
#define PL_CONFIG_HAS_TRIGGER   (1) /* support for triggers */
#define PL_CONFIG_HAS_BUZZER    (1 && PL_CONFIG_BOARD_IS_ROBO) /* support for buzzer */
#define PL_CONFIG_HAS_DEBOUNCE  (1) /* support for debouncing */

/* Allgemein */
#define PL_CONFIG_HAS_RTOS        (1) /* RTOS support */
#define PL_CONFIG_HAS_SHELL       (1) /* shell support */
#define PL_CONFIG_HAS_SHELL_QUEUE (1 && PL_CONFIG_HAS_SHELL) /* shell queue support */
#define PL_CONFIG_HAS_BLUETOOTH   (1) /* bluetooth support */
#define PL_CONFIG_HAS_USB_CDC     (1) /* USB CDC support */
#define PL_CONFIG_HAS_SEGGER_RTT  (1) /* Segger RTT support */

/* Platform spezifisch*/
#if PL_CONFIG_BOARD_IS_ROBO
	#define PL_CONFIG_HAS_REFLECTANCE (0) /* relflectance sensor support */
	#define PL_CONFIG_HAS_MOTOR       (0) /* motor support */
	#define PL_CONFIG_HAS_QUADRATURE  (0) /* quadratur encoder support */
	#define PL_CONFIG_HAS_MOTOR_TACHO (0) /* motor tacho support */
	#define PL_CONFIG_HAS_PID         (0) /* PID support */
	#define PL_CONFIG_HAS_DRIVE       (0) /* drive support */
	#define PL_CONFIG_HAS_TURN        (0) /* turn support */
	#define PL_CONFIG_HAS_LINE_FOLLOW (0) /* line follower support */
	#define PL_CONFIG_HAS_RADIO       (0) /* radio support */
	#define RNET_CONFIG_REMOTE_STDIO  (0 && PL_CONFIG_HAS_RADIO) /* radio stdio support */
	#define PL_CONFIG_HAS_REMOTE      (0) /* remote support */
	#define PL_CONFIG_HAS_LINE_MAZE   (0) /* maze solving support */
#elif PL_CONFIG_BOARD_IS_FRDM
	// Config fuer FRDM Board ToDo: Steffi
#endif

/* interface */
void PL_Init(void); /* driver initialization */
void PL_Deinit(void); /* driver deinitialization */

#endif /* SOURCES_INTRO_COMMON_PLATFORM_H_ */
