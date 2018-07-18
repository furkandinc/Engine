#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.cpp"
class Transform : public Component {
public:
	Transform();
	void setPosition(float x, float y);
	float getX();
	float getY();
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

float Transform::getX() {
	return x;
}

float Transform::getY() {
	return y;
}


#endif