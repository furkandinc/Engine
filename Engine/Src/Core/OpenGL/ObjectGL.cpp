#ifndef OBJECTGL_CPP
#define OBJECTGL_CPP

#include "ObjectGL.h"
#include <stdlib.h>
#include <stdio.h>

ObjectGL::ObjectGL() {
	this->idStat = false;
	this->points = nullptr;
	this->dirty = false;
	this->id = 0;
}

void ObjectGL::setId(int id) {
	this->id = id;
	this->idStat = true;
}

bool ObjectGL::hasId() {
	return idStat;
}

int ObjectGL::getId() {
	return this->id;
}

PointGL * ObjectGL::getPoints() {
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

void ObjectGL::setPoints(PointGL * pts, int size) {
	//printf("objectgl:setpoints\n");
	free(this->points);
	this->points = (PointGL * )malloc(sizeof(PointGL) * size);
	this->size = size;

	for (int i = 0; i < size; i++) {
		this->points[i] = pts[i];
	}
}

#endif

