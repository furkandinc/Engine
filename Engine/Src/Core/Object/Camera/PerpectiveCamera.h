#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera {
public:
	PerspectiveCamera();
	mat4 getProjection();
	
	void setFov(float fov);
	void setAspect(float aspect);
	void setDepth(float min, float max);
	float getFov();
	float getAspect();
	float getDepthMin();
	float getDepthMax();

private:
	float fov;
	float aspect;
	float dMin;
	float dMax;
};

#endif
