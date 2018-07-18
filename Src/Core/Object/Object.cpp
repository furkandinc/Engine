#ifndef OBJECT_H
#define OBJECT_H

#include "..\Component\Component.cpp"
#include "..\Component\Transform.cpp"
#include "..\Component\Mesh.cpp"
#include <stdlib.h>

class Object {
public:

	Object() {
		componentList = (Component **)malloc(sizeof(Component *) * 10);
		componentCount = 0;
		addComponent((Component *) new Transform());
		addComponent((Component *) new Mesh());
	};
	void addComponent(Component * component) {
		componentList[componentCount] = component;
		componentCount++;
	};

	template <typename T>
	Component * getComponent() {
		int i;
		for (i = 0; i<componentCount; i++) {
			Component * component = componentList[i];
			if (typeid(*component) == typeid(T)) {
				return component;
			}
		}
	};

private:
	Component ** componentList;
	int componentCount;
};

#endif