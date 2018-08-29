#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera {
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

#endif