#pragma once

#include "../dllexp.h"
#include "../OpenGL/ObjectGL.h"
#include "../Physics/Boundary.h"

class DLLDIR  Mesh {
public:
	virtual ObjectGL * getObjectGL() = 0;
	virtual Boundary * getBoundary() = 0;
};