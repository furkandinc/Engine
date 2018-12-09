#pragma once

#include "../dllexp.h"
#include "../OpenGL/ObjectGL.h"

class DLLDIR Boundary {
public:
	Boundary();
	void setLeft(float left);
	void setRight(float right);
	void setTop(float top);
	void setBottom(float bottom);
	void setNear(float n);
	void setFar(float f);
	ObjectGL * getObjectGL();

private:
	float red, green, blue, alpha;
	float left, right; //X
	float top, bottom; //Y
	float nearZ, farZ; //Z
	void cubeMesh();
	void quad(PointGL * pointBuffer, int indexStart, PointGL p1, PointGL p2, PointGL p3, PointGL p4);
	ObjectGL * objectGL;
};