/*
 * global.h
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "button.h"
#include "software_timer.h"
#include "display.h"
#include "fsm_manual.h"
#include "fsm_automatic.h"
#include "scheduler.h"

extern int status;

//#define TOP_BOT		0
//#define LEFT_RIGHT	1
//#define ALL			2
#define LED_TEST		0
#define LED_CHANGE		1
#define SEG_TIMER		2
#define COUNTDOWN_TIMER	3

#define INIT			4

#define RED_GREEN		30
#define RED_AMBER		31
#define GREEN_RED		32
#define AMBER_RED		33

#define RED				34
#define AMBER			35
#define GREEN			36


#define AUTO_RED		5
#define AUTO_AMBER		6
#define AUTO_GREEN		7

#define RED_MODE		20
#define AMBER_MODE		21
#define GREEN_MODE		22

extern int status;

extern int SevenSEGbuffer[4];

extern int blink_frequent;
extern int red_duration;
extern int amber_duration;
extern int green_duration;

extern int red_sec;
extern int amber_sec;
extern int green_sec;

#endif /* INC_GLOBAL_H_ */
