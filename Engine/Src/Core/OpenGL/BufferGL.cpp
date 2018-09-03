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
	materials = new ArrayList<Material>();
}

PointGL * BufferGL::getPoints() {
	return this->points->toArray();
}

int BufferGL::getNumPoints() {
	return this->points->getCount();
}

mat4 * BufferGL::getMatrices() {
	return this->matrices->toArray();
}

Integer * BufferGL::getSizes() {
	return this->sizes->toArray();
}

Integer * BufferGL::getIDs() {
	return this->ids->toArray();
}

Material * BufferGL::getMaterials() {
	return this->materials->toArray();
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
	ObjectGL * objectGL = object->getComponent<Renderer>()->getMesh()->getObjectGL();
	Material * material = object->getComponent<Renderer>()->getMaterial();
	Transform * transform = object->getComponent<Transform>();
	
	if (!objectGL->hasId()) {
		objectGL->setId(generateID());
	}

	int id = objectGL->getId();
	int index = indexOfId(id);
	if (index < 0) {
		//printf("Buffergl:add:index<0 id:%d\n", id);
		addToArray(objectGL->getPoints(), objectGL->getPointsSize());
		/*DEBUG*/
		PointGL dbPoints[1000];
		int db;
		for (db = 0; db < objectGL->getPointsSize() && db < 1000; db++) {
			dbPoints[db] = objectGL->getPoints()[db];
		}
		/*DEBUG*/
		matrices->add(transform->generateMatrix());
		sizes->add(objectGL->getPointsSize());
		ids->add(id);
		materials->add(*material);
		count++;
		objectGL->setDirty(false);
		dirty = true;
	}
	else {
		matrices->set(index,transform->generateMatrix());
		materials->set(index, *material);
		if (objectGL->isDirty()) {
			ArrayList<PointGL> * temp = new ArrayList<PointGL>();
			int newSize = objectGL->getPointsSize();
			int offset = 0;
			for (int i = 0; i < count; i++) {
				if (i != index) {
					for (int j = 0; j < sizes->get(i).get(); j++) {
						temp->add(points->get(offset + j));
					}
				}
				else {
					PointGL * newPoints = objectGL->getPoints();
					for (int j = 0; j < newSize; j++) {
						temp->add(newPoints[j]);
					}
				}

				offset += sizes->get(i).get();
			}
			sizes->set(index, Integer(newSize));
			free(points);
			points = temp;
			objectGL->setDirty(false);
			dirty = true;
		}
	}
}

void BufferGL::remove(Object * object) {
	Renderer * renderer = object->getComponent<Renderer>();
	Mesh * mesh = renderer->getMesh();
	ObjectGL * objectGL = mesh->getObjectGL();
	int id = objectGL->getId();
	int index = indexOfId(id);
	ids->set(index, Integer(-1));
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

#endif