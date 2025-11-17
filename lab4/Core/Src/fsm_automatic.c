/*
 * fsm_automatic.c
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */


#include "fsm_automatic.h"


void fsm_automatic_run(){
	switch (status){
	case INIT:
		clearAllLEDs();
		clearENs();
		clear7SEG();
		red_sec = red_duration/100;
		amber_sec = amber_duration/100;
		green_sec = green_duration/100;
		if (isButtonPressed(0)){
			setTimer(LED_CHANGE, green_duration);
			setTimer(COUNTDOWN_TIMER, 100);
			update_SevenSEGbuffer(red_sec, green_sec);
			status = RED_GREEN;
		}
		break;
	case RED_GREEN:
		setLEDs(RED_GREEN);
		/*if (isTimerExpired(COUNTDOWN_TIMER)){
			update_SevenSEGbuffer(--red_sec, --green_sec);
			setTimer(COUNTDOWN_TIMER, 100);
		}*/
		countdownUpdate(&red_sec, &green_sec);
		if (isTimerExpired(LED_CHANGE)){
			//green_sec = green_duration/100;
			resetCountdown();
			setTimer(COUNTDOWN_TIMER, 100);
			update_SevenSEGbuffer(red_sec, amber_sec);
			status = RED_AMBER;
			setTimer(LED_CHANGE, amber_duration);
		}
		modeChangeCheck();
		break;
	case RED_AMBER:
		setLEDs(RED_AMBER);
		/*if (isTimerExpired(COUNTDOWN_TIMER)){
			update_SevenSEGbuffer(--red_sec, --amber_sec);
			setTimer(COUNTDOWN_TIMER, 100);
		}*/
		countdownUpdate(&red_sec, &amber_sec);
		if (isTimerExpired(LED_CHANGE)){
			/*red_sec = red_duration/100;
			amber_sec = amber_duration/100;*/
			resetCountdown();
			setTimer(COUNTDOWN_TIMER, 100);
			update_SevenSEGbuffer(green_sec, red_sec);
			status = GREEN_RED;
			setTimer(LED_CHANGE, green_duration);
		}
		modeChangeCheck();
		break;
	case GREEN_RED:
		setLEDs(GREEN_RED);
		/*if (isTimerExpired(COUNTDOWN_TIMER)){
			update_SevenSEGbuffer(--green_sec, --red_sec);
			setTimer(COUNTDOWN_TIMER, 100);
		}*/
		countdownUpdate(&green_sec, &red_sec);
		if (isTimerExpired(LED_CHANGE)){
			//green_sec = green_duration/100;
			resetCountdown();
			setTimer(COUNTDOWN_TIMER, 100);
			update_SevenSEGbuffer(amber_sec, red_sec);
			status = AMBER_RED;
			setTimer(LED_CHANGE, amber_duration);
		}
		modeChangeCheck();
		break;
	case AMBER_RED:
		setLEDs(AMBER_RED);
		/*if (isTimerExpired(COUNTDOWN_TIMER)){
			update_SevenSEGbuffer(--amber_sec, --red_sec);
			setTimer(COUNTDOWN_TIMER, 100);
		}*/
		countdownUpdate(&amber_sec, &red_sec);
		resetCountdown();
		if (isTimerExpired(LED_CHANGE)){
			/*red_sec = red_duration/100;
			amber_sec = amber_duration/100;*/
			resetCountdown();
			setTimer(COUNTDOWN_TIMER, 100);
			update_SevenSEGbuffer(red_sec, green_sec);
			status = RED_GREEN;
			setTimer(LED_CHANGE, green_duration);
		}
		modeChangeCheck();
		break;
	default:
		break;
	}
}

void modeChangeCheck(){
	if (isButtonPressed(0)){
		clearAllLEDs();
		red_sec = red_duration/100;
		amber_sec = amber_duration/100;
		green_sec = green_duration/100;
		update_SevenSEGbuffer(red_sec, 2);
		status = RED_MODE;
		setTimer(LED_CHANGE, blink_frequent);
	}
}

void countdownUpdate(int *light1, int *light2) {
    if (isTimerExpired(COUNTDOWN_TIMER)) {
        if (*light1 > 0) (*light1)--;
        if (*light2 > 0) (*light2)--;
        update_SevenSEGbuffer(*light1, *light2);
        setTimer(COUNTDOWN_TIMER, 100);
    }
}

void resetCountdown() {
    if (red_sec <= 0) red_sec = red_duration / 100;
    if (amber_sec <= 0) amber_sec = amber_duration / 100;
    if (green_sec <= 0) green_sec = green_duration / 100;
}
