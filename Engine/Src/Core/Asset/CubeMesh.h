#pragma once

#include "Mesh.h"
#include "../dllexp.h"

class DLLDIR CubeMesh : public Mesh {
public:
	CubeMesh();
	ObjectGL * getObjectGL();
	Boundary * getBoundary();

	// Generable
	void * generate();
	int dispose();
private :
	void cubeMesh();
	void quad(PointGL * pointBuffer, int indexStart, vec4 p1, vec4 p2, vec4 p3, vec4 p4, vec3 normal);
	ObjectGL * objectGL;
	Boundary * boundary;
};
