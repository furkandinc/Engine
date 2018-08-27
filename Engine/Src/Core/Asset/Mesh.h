#ifndef MESH_H
#define MESH_H

#include "../OpenGL/ObjectGL.h"
#include "../Util/Boundary.h"

class Mesh {
public:
	virtual ObjectGL * getObjectGL() = 0;
	virtual void setColor(int r, int g, int b) = 0;
	virtual Boundary * getBoundary() = 0;
};

#endif