/*
 * fsm_manual.c
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */


#include "fsm_manual.h"

int red_tmp_duration = 0, amber_tmp_duration = 0, green_tmp_duration = 0;

void fsm_manual_run(){
	switch (status){
		case RED_MODE:
			if (isTimerExpired(LED_CHANGE)) {
				blinkLEDs(RED);
				setTimer(LED_CHANGE, 50);
			}
			if (isButtonPressed(0)){
				if (red_tmp_duration == 0) red_tmp_duration = red_duration;
				clearAllLEDs();
				status = AMBER_MODE;
				update_SevenSEGbuffer(amber_sec, 3);
				setTimer(LED_CHANGE, 50);
			}
			if (isButtonPressed(1)){
				red_sec++;
				if (red_sec >= 100) red_sec = 1;
				int original_total = green_duration + amber_duration;
				                if (original_total > 0) {
				                    amber_sec = (red_sec * amber_duration) / original_total;
				                    if (amber_sec < 1) amber_sec = 1;

				                    green_sec = red_sec - amber_sec;
				                    if (green_sec < 1) {
				                        green_sec = 1;
				                        amber_sec = red_sec - 1;
				                    }
				                }
				update_SevenSEGbuffer(red_sec, 2);
			}
			if (isButtonPressed(2)){
				red_tmp_duration = red_sec * 100;
				amber_tmp_duration = amber_sec * 100;
				green_tmp_duration = green_sec * 100;
			}
			break;

		case AMBER_MODE:
		            if (isTimerExpired(LED_CHANGE)) {
		                blinkLEDs(AMBER);
		                setTimer(LED_CHANGE, 50);
		            }
		            if (isButtonPressed(0)){
		                if (amber_tmp_duration == 0) amber_tmp_duration = amber_duration;
		                clearAllLEDs();
		                status = GREEN_MODE;
		                update_SevenSEGbuffer(green_sec, 4);
		                setTimer(LED_CHANGE, 50);
		            }
		            if (isButtonPressed(1)){
		                amber_sec++;
		                if (amber_sec >= 100) amber_sec = 1;

		                // TỰ ĐỘNG CẬP NHẬT: red = amber + green (giữ green cố định)
		                red_sec = amber_sec + green_sec;
		                if (red_sec >= 100) {
		                    red_sec = 99;
		                    amber_sec = red_sec - green_sec;
		                }

		                update_SevenSEGbuffer(amber_sec, 3);
		            }
		            if (isButtonPressed(2)){
		                amber_tmp_duration = amber_sec * 100;
		                red_tmp_duration = red_sec * 100;      // Cập nhật red luôn
		                green_tmp_duration = green_sec * 100;
		            }
		            break;
		case GREEN_MODE:
			if (isTimerExpired(LED_CHANGE)) {
				blinkLEDs(GREEN);
				setTimer(LED_CHANGE, 50);
			}
			if (isButtonPressed(1)){
				green_sec++;
				if (green_sec >= 100) green_sec = 1;
				// TỰ ĐỘNG CẬP NHẬT: red = amber + green (giữ amber cố định)
				                red_sec = amber_sec + green_sec;
				                if (red_sec >= 100) {
				                    red_sec = 99;
				                    green_sec = red_sec - amber_sec;
				   }
				update_SevenSEGbuffer(green_sec, 4);
			}
			if (isButtonPressed(2)){
				green_tmp_duration = green_sec * 100;
				red_tmp_duration = red_sec * 100;
				amber_tmp_duration = amber_sec * 100;

			}
			if (isButtonPressed(0)){
				if (green_tmp_duration == 0) green_tmp_duration = green_duration;
				clearAllLEDs();
				if ((green_tmp_duration + amber_tmp_duration) == red_tmp_duration){
					red_duration = red_tmp_duration;
					amber_duration = amber_tmp_duration;
					green_duration = green_tmp_duration;
				}
				red_tmp_duration = amber_tmp_duration = green_tmp_duration = 0;
				red_sec = red_duration/100;
				amber_sec = amber_duration/100;
				green_sec = green_duration/100;
				update_SevenSEGbuffer(red_sec, green_sec);
				status = RED_GREEN;
				setTimer(LED_CHANGE, green_duration);
				setTimer(COUNTDOWN_TIMER, 100);
			}

			break;

		default:
			break;
	}
}
