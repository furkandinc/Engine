#pragma once

#include "../dllexp.h"

class Object;

class DLLDIR CollisionListener {
public:
	virtual void onCollide(Object * object) = 0;
};
