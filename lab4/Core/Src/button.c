#include "global.h"

GPIO_PinState buttonBuffer[NUM_OF_BUTTON] = {RELEASED};

GPIO_PinState debounceBuffer_1[NUM_OF_BUTTON] = {RELEASED};
GPIO_PinState debounceBuffer_2[NUM_OF_BUTTON] = {RELEASED};
GPIO_PinState debounceBuffer_3[NUM_OF_BUTTON] = {RELEASED};

GPIO_TypeDef* buttonPort[NUM_OF_BUTTON] = {BUTTON_0_GPIO_Port, BUTTON_1_GPIO_Port, BUTTON_2_GPIO_Port};
uint16_t buttonPin[NUM_OF_BUTTON] = {BUTTON_0_Pin, BUTTON_1_Pin, BUTTON_2_Pin};


int buttonFlag[NUM_OF_BUTTON] = {0};
int LongPressTimer[NUM_OF_BUTTON] = {0};

void getKeyInput(){
	for (int i=0; i < NUM_OF_BUTTON; i++){
		debounceBuffer_1[i] = debounceBuffer_2[i];
		debounceBuffer_2[i] = debounceBuffer_3[i];
		debounceBuffer_3[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);
		if ((debounceBuffer_1[i] == debounceBuffer_2[i]) && (debounceBuffer_2[i] == debounceBuffer_3[i])){
			if (buttonBuffer[i] != debounceBuffer_3[i]){
				buttonBuffer[i] = debounceBuffer_3[i];
				if (buttonBuffer[i] == PRESSED){
					buttonFlag[i] = 1;
					LongPressTimer[i] = 100;
				}
			} else{
				LongPressTimer[i]--;
				if (LongPressTimer[i] <= 0) buttonBuffer[i] = RELEASED;
			}
		}
	}
}

int isButtonPressed(int index){
	if (index >= NUM_OF_BUTTON) return 0;
	if (buttonFlag[index] == 1) {
		buttonFlag[index] = 0;
		return 1;
	}
	return 0;
}
