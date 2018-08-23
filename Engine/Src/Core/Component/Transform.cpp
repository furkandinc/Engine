#ifndef TRANSFORM_CPP
#define TRANSFORM_CPP

#include "../includes/Angel.h"
#include "Transform.h"
#include "../Object/Object.h"

Transform::Transform() {
	this->position = vec3(0, 0, 0);
	this->scale = vec3(1, 1, 1);
	this->rotation = vec3(0, 0, 0);
}

void Transform::setPosition(vec3 position) {
	this->position = position;
}

void Transform::setScale(vec3 scale) {
	this->scale = scale;
}

void Transform::setRotation(vec3 rotation) {
	this->rotation = rotation;
}

vec3 Transform::getPosition() {
	return this->position;
}

vec3 Transform::getScale() {
	return this->scale;
}

vec3 Transform::getRotation() {
	return this->rotation;
}

vec3 Transform::globalPosition() {
	vec3 answer = position;
	Transform * parent = findParentTransform();
	if (parent != nullptr) {
		vec3 pRot = parent->globalRotation();
		vec4 result = RotateX(pRot.x) * RotateY(pRot.y) * RotateZ(pRot.z) * answer;
		answer = vec3(result.x, result.y, result.z);
		answer += parent->globalPosition();
	}

	return answer;
}

vec3 Transform::globalScale() {
	vec3 answer = scale;

	//Should it recursive?

	return answer;
}

vec3 Transform::globalRotation() {
	vec3 answer = rotation;
	
	Transform * parent = findParentTransform();
	if (parent != nullptr) {
		answer += parent->globalRotation();
	}

	return answer;
}

Transform * Transform::findParentTransform() {
	if (this->object != nullptr) {
		Object * parent = this->object->parent();
		if (parent != nullptr) {
			Transform * transform = parent->getComponent<Transform>();
			return transform;
		}
	}
	return nullptr;
}
#endif