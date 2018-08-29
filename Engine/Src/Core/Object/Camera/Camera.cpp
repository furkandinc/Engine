#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "Camera.h"
#include "../../Component/Transform.h"

void Camera::setRoll(float roll) {
	this->roll = roll;
}

vec4 Camera::getUpVector() {
	vec3 rot = getComponent<Transform>()->globalRotation();
	vec4 rolled = RotateX(roll) * vec4(0, 0, 1, 0);
	return RotateZ(rot.z) * RotateY(rot.y) * RotateX(rot.x) * rolled;
}

#endif