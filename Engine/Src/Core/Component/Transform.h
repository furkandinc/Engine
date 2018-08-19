#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

class Transform : public Component {
public:
	Transform();
	void setPosition(float x, float y);
	void setScale(float w, float y);
	float getX();
	float getY();
	float getW();
	float getH();
private:
	float x, y, w, h;
};

#endif