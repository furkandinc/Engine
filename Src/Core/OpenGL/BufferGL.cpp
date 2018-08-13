#ifndef BUFFERGL_CPP
#define BUFFERGL_CPP

#include "BufferGL.h"
#include <stdio.h>

BufferGL::BufferGL() {
	count = 0;
	lastGeneratedID = 100;
	
	points = new ArrayList<PointGL>();
	matrices = new ArrayList<mat4>();
	sizes = new ArrayList<Integer>();
	ids = new ArrayList<Integer>();
}

PointGL * BufferGL::getPoints() {
	return this->points->toArray();
}

int BufferGL::getNumPoints() {
	return this->points->size();
}

mat4 * BufferGL::getMatrices() {
	return this->matrices->toArray();
}

Integer * BufferGL::getSizes() {
	return this->sizes->toArray();
}

int BufferGL::getCount() {
	return this->count;
}

bool BufferGL::getDirty() {
	return this->dirty;
}

void BufferGL::setDirty(bool dirty) {
	this->dirty = dirty;
}

void BufferGL::add(Object * object) {
	ObjectGL * objectGL = object->getComponent<Mesh>()->getObjectGL();
	Transform * transform = object->getComponent<Transform>();
	if (!objectGL->hasId()) {
		objectGL->setId(generateID());
	}

	int id = objectGL->getId();
	int index = indexOfId(id);
	if (id < 0) {
		addToArray(objectGL->getPoints(), objectGL->getPointsSize());
		matrices->add(generateMatris(transform));
		sizes->add(objectGL->getPointsSize());
		ids->add(id);
		count++;
		objectGL->setDirty(false);
		dirty = true;
	}
	else {
		matrices->set(index, generateMatris(transform));
		// TODO if objectGL is dirty
	}
}

int BufferGL::generateID() {
	this->lastGeneratedID += 1;
	return lastGeneratedID;
}

int BufferGL::indexOfId(int id) {
	int i = 0;
	for (i = 0; i < count; i++) {
		if (id == ids->get(i).get()) {
			return i;
		}
	}
	return -1;
}

void BufferGL::addToArray(PointGL * points, int size) {
	int i;
	for (i = 0; i < size; i++) {
		this->points->add(points[i]);
	}
}

mat4 BufferGL::generateMatris(Transform * transform) {
	return Translate(vec3(transform->getX(), transform->getY(), 0));
}

#endif