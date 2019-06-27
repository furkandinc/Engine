#pragma once

#include <Engine.h>

class ExplosionScript : public Script {
public:
	void onStart();
	void onUpdate();
	void * generate();
	int dispose();
private:
	float startTime = 0;
};

