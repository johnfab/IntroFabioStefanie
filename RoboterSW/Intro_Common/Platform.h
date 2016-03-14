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

/* check local platform configuration */
#if PL_LOCAL_CONFIG_BOARD_IS_ROBO
  #define PL_CONFIG_BOARD_IS_FRDM   (0)
  #define PL_CONFIG_BOARD_IS_ROBO   (1)
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


/* driver configuration */
#define PL_CONFIG_HAS_LEDS      (1) /* LED driver */
#define PL_CONFIG_HAS_EVENTS    (1) /* event driver */
#define PL_CONFIG_HAS_TIMER     (1) /* timer interrupts */
#define PL_CONFIG_HAS_KEYS      (1) /* support for keys */

/* interfaces */
void PL_Init(void); /* driver initialization */
void PL_Deinit(void); /* driver deinitialization */

#endif /* SOURCES_INTRO_COMMON_PLATFORM_H_ */
