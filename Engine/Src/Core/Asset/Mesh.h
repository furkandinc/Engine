#pragma once

#include "../dllexp.h"
#include "../OpenGL/ObjectGL.h"
#include "../Physics/Boundary.h"
#include "../Generable.h"
#include "../Asset/Resource.h"

class DLLDIR  Mesh: public Generable {
public:
	Mesh();
	void setObjectGL(ObjectGL * objectGL);

	ObjectGL * getObjectGL();
	Boundary * getBoundary();

	void * generate();
	int dispose();
private:
	ObjectGL * objectGL;
	Boundary * boundary;

};