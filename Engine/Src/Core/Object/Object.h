#ifndef OBJECT_H
#define OBJECT_H

#include "..\Component\Component.h"
#include "..\Component\Transform.h"
#include "..\Component\Mesh.h"
#include <stdlib.h>
#include <stdio.h>
#include <utility>

class Object {
public:

	Object();

	void addComponent(Component * component);
	template <typename T> T * getComponent();
	
	Object * parent();
	Object ** children();
	int childCount();
	void addChild(Object * object);
	void removeChild(Object * object);

protected:
	void setParent(Object * parent);

private:
	Component ** componentList;
	int componentCount;
};

template<typename T>
T * Object::getComponent() {
	if (std::is_base_of<Component, T>::value) {
		int i;
		for (i = 0; i < componentCount; i++) {
			Component * component = componentList[i];
			if (T * v = dynamic_cast<T *>(component)) {
				return v;
			}
		}
	}
	return nullptr;
};
#endif