/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS

#include "RTOS.h"
#include "FRTOS1.h"
#include "LED.h"
#include "Event.h"
#include "Keys.h"
#include "Application.h"



/* Main Task */
static void Task_MainTask (void *pvParameters) {
	(void)pvParameters; /* avoid compiler warning */
	for (;;) {
		LED1_Neg();
		FRTOS1_vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

/* ---------------------------------------------------------------------------------------------- */
/* ----- RTOS from here ------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------- */

void RTOS_Run(void) {
  FRTOS1_vTaskStartScheduler();  /* does usually not return! */
}

void RTOS_Init(void) {
  /* Create Main Task */
	if(xTaskCreate(Task_MainTask, "MainTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
		for(;;){
			/* Only in the case of an error */
		}
	}
}

void RTOS_Deinit(void) {
  /* nothing needed for now */
}

#endif /* PL_CONFIG_HAS_RTOS */
