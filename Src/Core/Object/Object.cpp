#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "Object.h"

Object::Object() {
	componentList = (Component **)malloc(sizeof(Component *) * 10);
	componentCount = 0;
	addComponent((Component *) new Transform());
	addComponent((Component *) new Mesh());
};

void Object::addComponent(Component * component) {
	componentList[componentCount] = component;
	componentCount++;
};

template <typename T>
T * Object::getComponent() {
	int i;
	for (i = 0; i<componentCount; i++) {
		Component * component = componentList[i];
		if (typeid(*component) == typeid(T)) {
			return component;
		}
	}
};

#endif