#ifndef PERSPECTIVE_CAMERA_CPP
#define PERSPECTIVE_CAMERA_CPP

#include "PerpectiveCamera.h"
#include "../../Component/Renderer.h"
#include "../../Component/Transform.h"



PerspectiveCamera::PerspectiveCamera(){
	Renderer * renderer = getComponent<Renderer>();
	renderer->setMesh(nullptr); //don't render
	Transform * transform = getComponent<Transform>();

	//default initializations
	fov = 90;
	aspect = 1280/720.0;
	dMin = 1;
	dMax = 1000000;
	roll = 0;
	transform->setPosition(vec3(0, 00, 00));
	transform->setRotation(vec3(0, 0, 0));
}

mat4 PerspectiveCamera::getProjection() {
	return Perspective(fov, aspect, dMin, dMax);
}
void PerspectiveCamera::setFov(float fov){
	this->fov = fov;
}
void PerspectiveCamera::setAspect(float aspect){
	this->aspect = aspect;
}
void PerspectiveCamera::setDepth(float min, float max){
	this->dMin = min;
	this->dMax = max;
}
float PerspectiveCamera::getFov(){
	return fov;
}
float PerspectiveCamera::getAspect() {
	return aspect;
}
float PerspectiveCamera::getDepthMin(){
	return dMin;
}
float PerspectiveCamera::getDepthMax() {
	return dMax;
}
#endif