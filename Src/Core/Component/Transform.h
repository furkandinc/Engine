#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

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

#endif