#ifndef TRANSFORM_CPP
#define TRANSFORM_CPP

#include "Transform.h"

Transform::Transform() {
	this->x = 0;
	this->y = 0;
}

void Transform::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

float Transform::getX() {
	return x;
}

float Transform::getY() {
	return y;
}

#endif