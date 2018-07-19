#ifndef OBJECT_H
#define OBJECT_H

#include "..\Component\Component.h"
#include "..\Component\Transform.h"
#include "..\Component\Mesh.h"
#include <stdlib.h>

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

template<typename T>
T * Object::getComponent() {
	int i;
	for (i = 0; i<componentCount; i++) {
		Component * component = componentList[i];
		if (T * v = dynamic_cast<T *>((T * ) component)) {
			return v;
		}
	}
	return nullptr;
};
#endif