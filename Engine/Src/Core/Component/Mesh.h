#ifndef MESH_H
#define MESH_H

#include <stdlib.h>

#include "Component.h"
#include "../OpenGL/ObjectGL.h"

class Mesh : public Component{
public:
	Mesh();
	void setColor(int r, int g, int b);

	ObjectGL * getObjectGL();

private:
	void squareMesh();

	float red, green, blue, alpha;

	ObjectGL * objectGL;
};

#endif