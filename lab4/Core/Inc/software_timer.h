/*
 * software_timer.h
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

void setTimer(int index, int duration);
int isTimerExpired(int index);
void timerRun();


#endif /* INC_SOFTWARE_TIMER_H_ */
