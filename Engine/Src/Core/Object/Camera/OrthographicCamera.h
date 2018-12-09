#pragma once

#include "Camera.h"
#include "../../dllexp.h"

class DLLDIR OrthographicCamera : public Camera {
public:
	OrthographicCamera();
	mat4 getProjection();
	
	void setWidth(float width);
	void setHeight(float height);
	void setDepth(float min, float max);

	float getWidth();
	float getHeight();
	float getDepthMin();
	float getDepthMax();
private:
	float width, height, dMin, dMax;
};