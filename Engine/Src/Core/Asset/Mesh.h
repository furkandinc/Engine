#pragma once

#include "../dllexp.h"
#include "../OpenGL/ObjectGL.h"
#include "../Physics/Boundary.h"
#include "../Generable.h"

class DLLDIR  Mesh: public Generable {
public:
	virtual ObjectGL * getObjectGL() = 0;
	virtual Boundary * getBoundary() = 0;

	virtual void * generate() = 0;
	virtual int dispose() = 0;
};