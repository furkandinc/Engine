#pragma once

#include "../includes/Angel.h"

class TextureGL {
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
private:
	GLuint id;
	GLubyte * data;
	int width, height;
	bool dirty;
};