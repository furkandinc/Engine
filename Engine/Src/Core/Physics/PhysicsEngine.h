#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "../Object/ObjectHandler.h"

class PhysicsEngine {
public:
	PhysicsEngine();
	void tick();
	void setObjectHandler(ObjectHandler * objectHandler);
private:
	ObjectHandler * objectHandler;
};
#endif