/*
 * Platform.h
 *
 *  Created on: 01.03.2016
 *      Author: fabio
 */

#ifndef PLATFORM_H
#define PLATFORM_H

// include the local platform to find out what platform we have (LOCAL_PLATFOR_IS_...)
#include "Local_Platform.h"

// define our platform
#if LOCAL_PLATFORM_IS_FRDM
	#define PLATFORM_IS_FRDM (1)
	#define PLATFORM_IS_ROBO (0)
#elif LOCAL_PLATFORM_IS_ROBO
	#define PLATFORM_IS_FRDM (0)
	#define PLATFORM_IS_ROBO (1)
#else
	#error "The board type is not specified in Local_Platform.h"
#endif

// define LEDs
#if PLATFORM_IS_FRDM
	#define PL_HAS_LED (1)
	#define PL_NOF_LED (3)
#elif PLATFORM_IS_ROBO
	#define PL_HAS_LED (1)
	#define PL_NOF_LED (2)
#endif



#endif /* PLATFORM_H_ */
