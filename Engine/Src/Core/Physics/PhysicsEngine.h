#pragma once

#include "../dllexp.h"
#include "../Object/ObjectHandler.h"

class DLLDIR PhysicsEngine {
public:
	PhysicsEngine();
	void tick();
	void setObjectHandler(ObjectHandler * objectHandler);
private:
	ObjectHandler * objectHandler;
};