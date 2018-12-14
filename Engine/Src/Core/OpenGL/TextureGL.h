#pragma once

#include "../dllexp.h"
#include "../includes/Angel.h"
#include "../Generable.h"
#include "../Asset/Resource.h"

class DLLDIR TextureGL: public Generable {
public:
	TextureGL(Resource resource);
	void setDirty(bool dirty);
	bool getDirty();
	//void setData(GLubyte * bytes, int w, int h);
	GLubyte * getData();
	void setId(GLuint id);
	GLuint getId();
	int getWidth();
	int getHeight();

	//Generable
	void * generate();
	int dispose();
private:
	GLuint id;
	bool dirty;
	Resource resource;
};