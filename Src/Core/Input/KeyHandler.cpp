#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include "Keys.cpp"
#include <stdlib.h>

#endif
class KeyHandler {

public:
	KeyHandler();
	int getKeyStatus(int key);
	void keyPressed(int key);
	void keyReleased(int key);
	void tick();
private:
	const static enum Push : int { PUSHED, NOTPUSHED};
	int * pushList;
	int * keyList;
};

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