#ifndef KEYHANDLER_CPP
#define KEYHANDLER_CPP

#include "KeyHandler.h"
KeyHandler::KeyHandler() {
	keyList = (int *)malloc(Keys::COUNT * sizeof(int));
	pushList = (int *)malloc(Keys::COUNT * sizeof(int));
	for (int i = 0; i < Keys::COUNT; i++) {
		pushList[i] = 
		keyList[i] = Keys::STATUS_IDLE;
	}
}

int KeyHandler::getKeyStatus(int key) {
	if (key < 0 || key >= Keys::COUNT) {
		return -1;
	}

	return keyList[key];
}

void KeyHandler::keyPressed(int key) {
	if (key < 0 || key >= Keys::COUNT) {
		return;
	}

	pushList[key] = Push::PUSHED;
}

void KeyHandler::keyReleased(int key) {
	if (key < 0 || key >= Keys::COUNT) {
		return;
	}

	pushList[key] = Push::NOTPUSHED;
}

void KeyHandler::tick() {
	for (int i = 0; i < Keys::COUNT; i++) {
		int key = keyList[i];
		int pushed = pushList[i];

		if (key == Keys::STATUS_IDLE) {
			if (pushed == Push::PUSHED) {
				keyList[i] = Keys::STATUS_PRESSED;
			}
			else {
				keyList[i] = Keys::STATUS_IDLE;
			}
		}
		else if (key == Keys::STATUS_PRESSED) {
			if (pushed == Push::PUSHED) {
				keyList[i] = Keys::STATUS_PRESS;
			}
			else {
				keyList[i] = Keys::STATUS_RELEASED;
			}
		}
		else if(key == Keys::STATUS_PRESS) {
			if (pushed == Push::PUSHED) {
				keyList[i] = Keys::STATUS_PRESS;
			}
			else {
				keyList[i] = Keys::STATUS_RELEASED;
			}
		}
		else {
			if (pushed == Push::PUSHED) {
				keyList[i] = Keys::STATUS_PRESSED;
			}
			else {
				keyList[i] = Keys::STATUS_IDLE;
			}
		}
	}
}
#endif