/*
 * fsm_automatic.h
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

#include "global.h"

void fsm_automatic_run();
void countdownUpdate(int *light1, int *light2);
void resetCountdown();
void modeChangeCheck();

#endif /* INC_FSM_AUTOMATIC_H_ */
