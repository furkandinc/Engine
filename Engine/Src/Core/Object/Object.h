#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include "../dllexp.h"

class Component;

class DLLDIR Object {
public:

	Object();

	void addComponent(Component * component);
	template <typename T> T * getComponent();
	Component * removeComponent(int index);

	Object * parent();
	Object ** children();
	int childCount();
	void addChild(Object * object);
	Object * removeChild(int index);

protected:
	virtual void abstraction();

private:
	Component ** componentList;
	int componentListCount;
	int componentListSize;

	Object ** childList;
	int childListCount;
	int childListSize;

	Object * parentObject;

	void resizeBuffers();
};

template<typename T>
T * Object::getComponent() {
	if (std::is_base_of<Component, T>::value) {
		int i;
		for (i = 0; i < componentListCount; i++) {
			Component * component = componentList[i];
			if (T * v = dynamic_cast<T *>(component)) {
				return v;
			}
		}
	}
	return nullptr;
};