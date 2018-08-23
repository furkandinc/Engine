#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "../includes/Angel.h"
class Transform : public Component {
public:
	Transform();
	void setPosition(vec3 position);
	void setScale(vec3 scale);
	void setRotation(vec3 rotation);
	
	vec3 getPosition();
	vec3 getScale();
	vec3 getRotation();

	vec3 globalPosition();
	vec3 globalScale();
	vec3 globalRotation();

private:
	vec3 position;
	vec3 scale;
	vec3 rotation;

	Transform * findParentTransform();
};

#endif