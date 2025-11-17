/*
 * button.h
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define PRESSED GPIO_PIN_RESET
#define RELEASED GPIO_PIN_SET
#define NUM_OF_BUTTON 3

void getKeyInput();
int isButtonPressed(int index);

#endif /* INC_BUTTON_H_ */

