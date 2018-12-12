#pragma once

#include "../dllexp.h"
#include "../includes/Angel.h"
#include "../Generable.h"

class DLLDIR TextureGL: public Generable {
public:
	TextureGL();
	void setDirty(bool dirty);
	bool getDirty();
	void setData(GLubyte * bytes, int w, int h);
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
	GLubyte * data;
	int width, height;
	bool dirty;
};