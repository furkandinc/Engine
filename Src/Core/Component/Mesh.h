#ifndef MESH_H
#define MESH_H

#include <stdlib.h>

#include "Renderable.h"
#include "Component.h"

class Mesh : public Component, Renderable {
public:
	Mesh();
	void setColor(int r, int g, int b);

	virtual ObjectGL * getObjectGL();

private:
	void squareMesh();

	int red, green, blue;

	ObjectGL * objectGL;
};

#endif