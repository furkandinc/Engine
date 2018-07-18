#ifndef OBJECTGL_CPP
#define OBJECTGL_CPP

#include "ObjectGL.h"


ObjectGL::ObjectGL() {
	this->idStat = false;
}

void ObjectGL::setId(int id) {
	this->id = id;
	this->idStat;
}

bool ObjectGL::hasId() {
	return idStat;
}

int ObjectGL::getId() {
	return this->id;
}

PointGL ** ObjectGL::getPoints() {
	return points;
}

void ObjectGL::setDirty(bool dirty) {
	this->dirty = dirty;
}

bool ObjectGL::isDirty() {
	return this->dirty;
}

int ObjectGL::getPointsSize() {
	return this->size;
}

void ObjectGL::setPoints(PointGL ** points, int size) {
		this->points = points;
		this->size = size;
}

#endif

