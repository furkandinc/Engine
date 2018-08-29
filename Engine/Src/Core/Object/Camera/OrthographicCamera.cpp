#ifndef ORTHOGRAPHIC_CAMERA_CPP
#define ORTHOGRAPHIC_CAMERA_CPP

#include "OrthographicCamera.h"
#include "../../Component/Transform.h"
#include "../../Component/Renderer.h"
OrthographicCamera::OrthographicCamera() {
	//default initializations
	width = 800;
	height = 600;
	dMin = 1;
	dMax = 1000000;
	roll = 0;
	
	Renderer * renderer = getComponent<Renderer>();
	renderer->setMesh(nullptr);
	Transform * transform = getComponent<Transform>();
	transform->setPosition(vec3(400, 300, 1000));
	transform->setRotation(vec3(-90, 90, 0));
}

mat4 OrthographicCamera::getProjection() {
	float w = width / 2.0;
	float h = height / 2.0;
	return Ortho(-w, w, -h, h, dMin, dMax);
}

#endif