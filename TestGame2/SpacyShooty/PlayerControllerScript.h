#pragma once

#include <Engine.h>

class PlayerControllerScript : public Script {
public:
	void onStart(void);
	void onUpdate(void);
	void * generate();
	int dispose();

	Object * player;
protected:
	int boundaryWidth = 700;
	int boundaryHeight = 720;
	int currentSpeedX = 0;
	int currentSpeedY = 0;
	int maxSpeed = 500;
};