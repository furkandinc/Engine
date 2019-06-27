#include "OrthographicCamera.h"
#include "../../Component/Transform.h"
#include "../../Component/Renderer.h"
OrthographicCamera::OrthographicCamera() {
	//default initializations
	width = 800;
	height = 600;
	dMin = 1;
	dMax = 1000000;
	
	Transform * transform = getComponent<Transform>();
	transform->setPosition(vec3(400, 300, 1000));
	transform->setRotation(vec3(-90, 90, 0));
}

mat4 OrthographicCamera::getProjection() {
	float w = width / 2.0;
	float h = height / 2.0;
	return Ortho(-w, w, -h, h, dMin, dMax);
}

void OrthographicCamera::setWidth(float width) {
	this->width = width;
}

void OrthographicCamera::setHeight(float height) {
	this->height = height;
}

void OrthographicCamera::setDepth(float min, float max) {
	dMin = min;
	dMax = max;
}

float OrthographicCamera::getWidth()
{
	return width;
}

float OrthographicCamera::getHeight()
{
	return height;
}

float OrthographicCamera::getDepthMin()
{
	return dMin;
}

float OrthographicCamera::getDepthMax()
{
	return dMax;
}