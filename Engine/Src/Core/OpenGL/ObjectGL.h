#pragma once

#include "PointGL.h"
#include "../dllexp.h"
#include "../Generable.h"
#include "../Asset/Resource.h"
#include "../includes/Angel.h"

class DLLDIR ObjectGL: public Generable {
public:
	ObjectGL(Resource resource);
	void setDirty(bool dirty);
	bool getDirty();
	void setId(GLuint id);
	GLuint getId();
	PointGL * getData();
	int getSize();
	//void setPoints(PointGL * points, int size);

	void * generate();
	int dispose();
private:
	GLuint id;
	bool dirty;
	Resource resource;
};