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
	void quad(PointGL * pointBuffer, int indexStart, PointGL p1, PointGL p2, PointGL p3, PointGL p4);

	float red, green, blue, alpha;

	ObjectGL * objectGL;
};

#endif