/*
 * display.h
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "global.h"

//void clearLEDs(int direct);
void clearAllLEDs();
//void setLEDs(int direct, int led);
void setLEDs(int led);
void blinkLEDs(int led);

void update7SEG(int index);
void display7SEG(int seg, int num);

void clearENs();

void clear7SEG();
void clear7SEG_1();
void clear7SEG_2();

void turnAll7SEG();
void turnAll7SEG_1();
void turnAll7SEG_2();

void update_SevenSEGbuffer(int timer, int mode);
#endif /* INC_DISPLAY_H_ */
