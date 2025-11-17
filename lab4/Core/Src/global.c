/*
 * global.c
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */


#include "global.h"

int status = INIT;

int blink_frequent = 50;
int red_duration = 500;
int amber_duration = 200;
int green_duration = 300;

int red_sec;
int amber_sec;
int green_sec;

int SevenSEGbuffer[4] = {0};
