#pragma once

#include <Engine.h>
#include "GameControllerScript.h"

class ForwardScript : public Script, public CollisionListener {
public:
	void onStart();
	void onUpdate();
	void * generate();
	int dispose();
	void onCollide(Object * object);

	vec3 movementSpeed;
	vec3 angularSpeed;

	Object * explosionPrefab;
	Object * hazardPrefab;
	GameControllerScript * gameScript;
protected:
	int minX = -200;
	int minY = -200;
	int maxX = 2000;
	int maxY = 2000;
};