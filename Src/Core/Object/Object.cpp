#ifndef OBJECT_H
#define OBJECT_H

#include "..\Component\Component.cpp"
#include "..\Component\Transform.cpp"
#include "..\Component\Mesh.cpp"
#include <stdlib.h>

#endif

class Object {
public:

	Object();
	void addComponent(Component * component);

	template <typename T>
	T * getComponent();

private:
	Component ** componentList;
	int componentCount;
};

Object::Object() {
	componentList = (Component **)malloc(sizeof(Component *) * 10);
	componentCount = 0;
	addComponent((Component * ) new Transform());
	addComponent((Component * ) new Mesh());
}

void Object::addComponent(Component * component) {
	componentList[componentCount] = component;
	componentCount++;
}

template <typename T>
Component * Object::getComponent() {
	int i;
	for (i = 0; i<componentCount; i++) {
		Component * component = componentList[i];
		if (typeid(*component) == typeid(T)) {
			return component;
		}
	}
}
