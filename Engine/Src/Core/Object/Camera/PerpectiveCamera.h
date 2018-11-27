#pragma once

#include "Camera.h"
#include "../../dllexp.h"

class DLLDIR PerspectiveCamera : public Camera {
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