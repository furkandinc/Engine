#ifndef BUFFERGL_CPP
#define BUFFERGL_CPP

#include "BufferGL.h"

BufferGL::BufferGL() {
	count = 0;
	lastGeneratedID = 100;
}

PointGL * BufferGL::getPoints() {
	return this->points.data;
}

int BufferGL::getNumPoints() {
	return this->points.size;
}

mat4 * BufferGL::getMatrices() {
	return this->matrices.data();
}

int * BufferGL::getSizes() {
	return this->sizes.data();
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
	ObjectGL * objectGL = object->getComponent<Renderable>()->getObjectGL();
	Transform * transform = object->getComponent<Transform>();
	if (!objectGL->hasId()) {
		objectGL->setId(generateID());
	}

	int id = objectGL->getId();
	int index = indexOfId(id);
	if (id < 0) {
		addToArray(objectGL->getPoints, objectGL->getPointsSize);
		matrices.push_back(generateMatris(transform));
		sizes.push_back(objectGL->getPointsSize);
		ids.push_back(id);
		count++;
		objectGL->setDirty(false);
		dirty = true;
	}
	else {
		matrices[index] = generateMatris(transform);
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
		if (id == ids[i]) {
			return i;
		}
	}
	return -1;
}

void BufferGL::addToArray(PointGL * points, int size) {
	int i;
	for (i = 0; i < size; i++) {
		this->points.push_back(points[i]);
	}
}

mat4 BufferGL::generateMatris(Transform * transform) {
	return Translate(vec3(transform->getX, transform->getY, 0));
}

#endif