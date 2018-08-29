#ifndef CAMERA_H
#define CAMERA_H

#include "../Object.h"
#include "../../includes/Angel.h"

class Camera: public Object {
public:
	virtual mat4 getProjection() = 0;
	void setRoll(float roll);
	vec4 getUpVector();
protected:
	float roll;
};

#endif