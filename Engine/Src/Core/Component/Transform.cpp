#ifndef TRANSFORM_CPP
#define TRANSFORM_CPP

#include "Transform.h"

Transform::Transform() {
	this->x = 0;
	this->y = 0;
	this->w = 1;
	this->h = 1;
}

void Transform::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

void Transform::setScale(float w, float h) {
	this->w = w;
	this->h = h;
}

float Transform::getX() {
	return x;
}

float Transform::getY() {
	return y;
}

float Transform::getW() {
	return w;
}

float Transform::getH() {
	return h;
}
#endif