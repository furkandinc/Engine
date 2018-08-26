#ifndef MESH_H
#define MESH_H

#include "../OpenGL/ObjectGL.h"

class Mesh {
public:
	virtual ObjectGL * getObjectGL() = 0;
	virtual void setColor(int r, int g, int b) = 0;
};

#endif