/*
 * software_timer.c
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */


#include "software_timer.h"
#define MAX_TIMER 10

int timer_counter[MAX_TIMER];
int timer_flag[MAX_TIMER];

void setTimer(int index, int duration){
	timer_counter[index] = duration;
	timer_flag[index] = 0;
}

int isTimerExpired(int index){
	if (timer_flag[index] == 0) return 0;
	return 1;
}

void timerRun(){
	for (int i = 0; i < MAX_TIMER; i++){
		if (timer_counter[i] > 0){
			timer_counter[i]--;
			if (timer_counter[i] <= 0) timer_flag[i] = 1;
		}
	}
}
