#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <Engine.h>

class ThiefScript : public Script, CollisionListener {
public:
	void onStart(void);
	void onUpdate(void);
	void onCollide(Object * object);

	Object * thief;
	Object * art;

	int boundaryWidth;
	int boundaryHeight;
private:
	int score;
};