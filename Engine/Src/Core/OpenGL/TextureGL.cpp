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
	this->id = id;
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
