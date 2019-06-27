#include "TextureGL.h"

TextureGL::TextureGL(Resource resource) {
	this->resource = resource;
	dirty = true;
}

void TextureGL::setDirty(bool dirty){
	this->dirty = dirty;
}

bool TextureGL::getDirty(){
	return dirty;
}

/*void TextureGL::setData(GLubyte * bytes, int w, int h){
	this->data = bytes;
	width = w;
	height = h;
	setDirty(true);
}*/

GLubyte * TextureGL::getData() {
	return (GLubyte *) resource.data;
}

void TextureGL::setId(GLuint id){
	this->id = id;
}

GLuint TextureGL::getId() {
	return id;
}

int TextureGL::getWidth() {
	return ((int* )resource.argv)[0];
}

int TextureGL::getHeight() {
	return ((int *)resource.argv)[1];
}

void * TextureGL::generate() {
	TextureGL * t = new TextureGL(resource);
	//t->setData(data, width, height);
	t->id = id;
	t->dirty = dirty;
	return t;
}

int TextureGL::dispose() {
	//free(data);
	return 0;
}