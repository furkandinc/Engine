#ifndef CUBEMESH_H
#define CUBEMESH_H

#include "Mesh.h"

class CubeMesh : public Mesh {
public:
	CubeMesh();
	void setColor(int r, int g, int b);
	ObjectGL * getObjectGL();

private :
	void cubeMesh();
	void quad(PointGL * pointBuffer, int indexStart, PointGL p1, PointGL p2, PointGL p3, PointGL p4);
	ObjectGL * objectGL;
	float red, green, blue, alpha;
};

#endif