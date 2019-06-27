#include "ObjectGL.h"
#include <stdlib.h>
#include <stdio.h>

ObjectGL::ObjectGL(Resource resource) {
	this->resource = resource;
	dirty = true;
}

void ObjectGL::setDirty(bool dirty) {
	this->dirty = dirty;
}

bool ObjectGL::getDirty() {
	return dirty;
}

PointGL * ObjectGL::getData() {
	return (PointGL *)resource.data;
}

void ObjectGL::setId(GLuint id) {
	this->id = id;
}

GLuint ObjectGL::getId() {
	return id;
}

int ObjectGL::getSize() {
	return resource.size;
}

void * ObjectGL::generate() {
	ObjectGL * o = new ObjectGL(resource);
	o->dirty = dirty;
	o->id = id;

	return o;
}

int ObjectGL::dispose() {
	return 0;
}