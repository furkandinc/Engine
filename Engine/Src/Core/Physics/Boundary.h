#pragma once

#include "../dllexp.h"
#include "../OpenGL/ObjectGL.h"
#include "../Generable.h"
#include "../Component/Transform.h"

class DLLDIR Boundary: public Generable {
public:
	Boundary();
	void setLeft(float left);
	void setRight(float right);
	void setTop(float top);
	void setBottom(float bottom);
	void setNear(float n);
	void setFar(float f);
	void setTransform(Transform * transform);
	bool collide(Boundary * boundary);

	//Generable
	void * generate();
	int dispose();
private:
	float left, right; //X
	float top, bottom; //Y
	float nearZ, farZ; //Z

	Transform * transform;

	float * generateBound();
};