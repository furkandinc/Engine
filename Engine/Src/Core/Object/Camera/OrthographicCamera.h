#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
	OrthographicCamera();
	mat4 getProjection();
private:
	float width, height, dMin, dMax;
};

#endif