#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <Engine.h>

float random(int a, int b);
class SnekScript : public Script, public CollisionListener {
public:
	void onStart(void);
	void onUpdate(void);
	void onCollide(Object * object);

	Object * player;
	Object * target;
private:
	int score;
	int boundaryWidth = 1280;
	int boundaryHeight = 720;
};