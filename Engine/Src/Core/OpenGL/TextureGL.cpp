#include "TextureGL.h"

TextureGL::TextureGL() {
	dirty = false;
}

void TextureGL::setDirty(bool dirty){
	this->dirty = dirty;
}

bool TextureGL::getDirty(){
	return dirty;
}

void TextureGL::setData(GLubyte * bytes, int w, int h){
	this->data = bytes;
	width = w;
	height = h;
	setDirty(true);
}

GLubyte * TextureGL::getData() {
	return data;
}

void TextureGL::setId(GLuint id){
	printf("TextureGL:setid\n");
	this->id = id;
	printf("TextureGL:setid end\n");
}

GLuint TextureGL::getId() {
	return id;
}

int TextureGL::getWidth() {
	return width;
}

int TextureGL::getHeight() {
	return height;
}

void * TextureGL::generate() {
	TextureGL * t = new TextureGL();
	int size = 3 * width * height;
	GLubyte * temp = (GLubyte *)malloc(sizeof(GLubyte) * size);
	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}
	t->setData(temp, width, height);

	return t;
}

int TextureGL::dispose() {
	free(data);
	return 0;
}