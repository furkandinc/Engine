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

	int red, green, blue;

	ObjectGL * objectGL;
};

#endif