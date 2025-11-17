/*
 * display.c
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */


#include "display.h"

void clearAllLEDs(){
	HAL_GPIO_WritePin(GPIOA, RED_1_Pin|AMBER_1_Pin|GREEN_1_Pin|RED_2_Pin|AMBER_2_Pin|GREEN_2_Pin, GPIO_PIN_SET);
}

void setLEDs(int led){
	clearAllLEDs();
	switch(led){
		case RED_GREEN:
			HAL_GPIO_WritePin(GPIOA, RED_1_Pin|GREEN_2_Pin, GPIO_PIN_RESET);
			break;
		case RED_AMBER:
			HAL_GPIO_WritePin(GPIOA, RED_1_Pin|AMBER_2_Pin, GPIO_PIN_RESET);
			break;
		case GREEN_RED:
			HAL_GPIO_WritePin(GPIOA, GREEN_1_Pin|RED_2_Pin, GPIO_PIN_RESET);
			break;
		case AMBER_RED:
			HAL_GPIO_WritePin(GPIOA, AMBER_1_Pin|RED_2_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
}

void blinkLEDs(int led){
	switch (led){
		case RED:
			HAL_GPIO_TogglePin(GPIOA, RED_1_Pin|RED_2_Pin);
			break;
		case AMBER:
			HAL_GPIO_TogglePin(GPIOA, AMBER_1_Pin|AMBER_2_Pin);
			break;
		case GREEN:
			HAL_GPIO_TogglePin(GPIOA, GREEN_1_Pin|GREEN_2_Pin);
			break;
	}
}

void display7SEG(int seg, int num){
	if (seg == 1){
		turnAll7SEG_1();
		switch (num){
			case 0:
				HAL_GPIO_WritePin(GPIOB, SEG1_6_Pin, GPIO_PIN_SET);
				break;
			case 1:
				clear7SEG_1();
				HAL_GPIO_WritePin(GPIOB, SEG1_1_Pin|SEG1_2_Pin, GPIO_PIN_RESET);
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOB, SEG1_2_Pin|SEG1_5_Pin, GPIO_PIN_SET);
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOB, SEG1_4_Pin|SEG1_5_Pin, GPIO_PIN_SET);
				break;
			case 4:
				HAL_GPIO_WritePin(GPIOB, SEG1_0_Pin|SEG1_3_Pin|SEG1_4_Pin, GPIO_PIN_SET);
				break;
			case 5:
				HAL_GPIO_WritePin(GPIOB, SEG1_1_Pin|SEG1_4_Pin, GPIO_PIN_SET);
				break;
			case 6:
				HAL_GPIO_WritePin(GPIOB, SEG1_1_Pin, GPIO_PIN_SET);
				break;
			case 7:
				clear7SEG_1();
				HAL_GPIO_WritePin(GPIOB, SEG1_0_Pin|SEG1_1_Pin|SEG1_2_Pin, GPIO_PIN_RESET);
				break;
			case 8:
				break;
			case 9:
				HAL_GPIO_WritePin(GPIOB, SEG1_4_Pin, GPIO_PIN_SET);
				break;
			default:
				clear7SEG();
				break;
		}
	} else if (seg == 2){
		turnAll7SEG_2();
		switch (num){
			case 0:
				HAL_GPIO_WritePin(GPIOB, SEG2_6_Pin, GPIO_PIN_SET);
				break;
			case 1:
				clear7SEG_2();
				HAL_GPIO_WritePin(GPIOB, SEG2_1_Pin|SEG2_2_Pin, GPIO_PIN_RESET);
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOB, SEG2_2_Pin|SEG2_5_Pin, GPIO_PIN_SET);
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOB, SEG2_4_Pin|SEG2_5_Pin, GPIO_PIN_SET);
				break;
			case 4:
				HAL_GPIO_WritePin(GPIOB, SEG2_0_Pin|SEG2_3_Pin|SEG2_4_Pin, GPIO_PIN_SET);
				break;
			case 5:
				HAL_GPIO_WritePin(GPIOB, SEG2_1_Pin|SEG2_4_Pin, GPIO_PIN_SET);
				break;
			case 6:
				HAL_GPIO_WritePin(GPIOB, SEG2_1_Pin, GPIO_PIN_SET);
				break;
			case 7:
				clear7SEG_2();
				HAL_GPIO_WritePin(GPIOB, SEG2_0_Pin|SEG2_1_Pin|SEG2_2_Pin, GPIO_PIN_RESET);
				break;
			case 8:
				break;
			case 9:
				HAL_GPIO_WritePin(GPIOB, SEG2_4_Pin, GPIO_PIN_SET);
				break;
			default:
				clear7SEG();
				break;
		}
	}
}

void update7SEG(int index){
	switch (index){
		case 0:
			//clearENs();
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
			display7SEG(1, SevenSEGbuffer[index]);
			break;
		case 1:
			//clearENs();
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
			display7SEG(1, SevenSEGbuffer[index]);
			break;
		case 2:
			//clearENs();
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
			display7SEG(2, SevenSEGbuffer[index]);
			break;
		case 3:
			//clearENs();
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
			display7SEG(2, SevenSEGbuffer[index]);
			break;
		default:
			break;
	}
}

void clearENs(){
	HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
}

void clear7SEG(){
	HAL_GPIO_WritePin(GPIOB, SEG1_0_Pin|SEG1_1_Pin|SEG1_2_Pin|SEG1_3_Pin
	                        |SEG1_4_Pin|SEG1_5_Pin|SEG1_6_Pin|SEG2_0_Pin
	                        |SEG2_1_Pin|SEG2_2_Pin|SEG2_3_Pin|SEG2_4_Pin
	                        |SEG2_5_Pin|SEG2_6_Pin, GPIO_PIN_SET);
}

void clear7SEG_1(){
	HAL_GPIO_WritePin(GPIOB, SEG1_0_Pin|SEG1_1_Pin|SEG1_2_Pin|SEG1_3_Pin
	                        |SEG1_4_Pin|SEG1_5_Pin|SEG1_6_Pin, GPIO_PIN_SET);
}

void clear7SEG_2(){
	HAL_GPIO_WritePin(GPIOB, SEG2_0_Pin|SEG2_1_Pin|SEG2_2_Pin|SEG2_3_Pin
							|SEG2_4_Pin|SEG2_5_Pin|SEG2_6_Pin, GPIO_PIN_SET);
}

void turnAll7SEG(){
	HAL_GPIO_WritePin(GPIOB, SEG1_0_Pin|SEG1_1_Pin|SEG1_2_Pin|SEG1_3_Pin
	                        |SEG1_4_Pin|SEG1_5_Pin|SEG1_6_Pin|SEG2_0_Pin
	                        |SEG2_1_Pin|SEG2_2_Pin|SEG2_3_Pin|SEG2_4_Pin
	                        |SEG2_5_Pin|SEG2_6_Pin, GPIO_PIN_RESET);
}

void turnAll7SEG_1(){
	HAL_GPIO_WritePin(GPIOB, SEG1_0_Pin|SEG1_1_Pin|SEG1_2_Pin|SEG1_3_Pin
	                        |SEG1_4_Pin|SEG1_5_Pin|SEG1_6_Pin, GPIO_PIN_RESET);
}

void turnAll7SEG_2(){
	HAL_GPIO_WritePin(GPIOB, SEG2_0_Pin|SEG2_1_Pin|SEG2_2_Pin|SEG2_3_Pin
							|SEG2_4_Pin|SEG2_5_Pin|SEG2_6_Pin, GPIO_PIN_RESET);
}

void update_SevenSEGbuffer(int timer, int mode){
	SevenSEGbuffer[0] = timer/10;
	SevenSEGbuffer[1] = timer%10;
	SevenSEGbuffer[2] = mode/10;
	SevenSEGbuffer[3] = mode%10;
}
