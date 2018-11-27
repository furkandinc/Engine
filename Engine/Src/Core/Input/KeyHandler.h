#pragma once

#include "Keys.h"
#include <stdlib.h>
#include "../dllexp.h"

class KeyHandler {

public:
	KeyHandler();
	int getKeyStatus(int key);
	void keyPressed(unsigned int keyCode);
	void keyReleased(unsigned int keyCode);
	void specialPressed(int keyCode);
	void specialReleased(int keyCode);
	void tick();
private:
	const static enum Push : int { PUSHED, NOTPUSHED };
	int * pushList;
	int * keyList;
};