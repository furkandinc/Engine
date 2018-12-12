#pragma once

#include <Engine.h>

class PoliceScript : public Script, public CollisionListener {
public:
	void onStart(void);
	void onUpdate(void);
	void onCollide(Object * object);

	//Generable
	void * generate();
	int dispose();

	Object * police;
	Object * thief;
	Object * art;

	int boundaryWidth;
	int boundaryHeight;
private:
	int score;
};