#ifndef CUBEMESH_H
#define CUBEMESH_H

#include "Mesh.h"

class CubeMesh : public Mesh {
public:
	CubeMesh();
	ObjectGL * getObjectGL();
	Boundary * getBoundary();

private :
	void cubeMesh();
	void quad(PointGL * pointBuffer, int indexStart, vec4 p1, vec4 p2, vec4 p3, vec4 p4, vec3 normal);
	ObjectGL * objectGL;
	Boundary * boundary;
};

#endif