#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include "../dllexp.h"
#include "../Generable.h"

class Component;

class DLLDIR Object: public Generable {
public:

	Object();

	void addComponent(Component * component);
	template <typename T> T * getComponent();
	bool removeComponent(int index);
	void setTag(const char * tag);
	const char * getTag();

	Object * parent();
	Object ** children();
	int childCount();
	void addChild(Object * object);
	Object * removeChild(int index);

	//Generable
	void * generate();
	int dispose();
protected:
	virtual void abstraction();
	const char * tag;

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