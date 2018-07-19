#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "Object.h"

Object::Object() {
	componentList = (Component **)malloc(sizeof(Component *) * 10);
	componentCount = 0;
	addComponent(new Transform());
	addComponent(new Mesh());
};

void Object::addComponent(Component * component) {
	componentList[componentCount] = component;
	componentCount++;
};



#endif