#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.cpp"

#endif

class Transform : public Component {
public:
	Transform();
	void setPosition(float x, float y);
	int getX();
	int getY();
private:
	float x;
	float y;
};

Transform::Transform() {
	this->x = 0;
	this->y = 0;
}

void Transform::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

int Transform::getX() {
	return x;
}

int Transform::getY() {
	return y;
}