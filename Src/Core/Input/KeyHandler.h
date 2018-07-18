#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include "Keys.h"
#include <stdlib.h>

class KeyHandler {

public:
	KeyHandler();
	int getKeyStatus(int key);
	void keyPressed(int key);
	void keyReleased(int key);
	void tick();
private:
	const static enum Push : int { PUSHED, NOTPUSHED };
	int * pushList;
	int * keyList;
};
#endif