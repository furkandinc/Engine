#ifndef MESH_H
#define MESH_H

#include "../OpenGL/ObjectGL.h"
#include "../Physics/Boundary.h"

class Mesh {
public:
	virtual ObjectGL * getObjectGL() = 0;
	virtual Boundary * getBoundary() = 0;
};

#endif