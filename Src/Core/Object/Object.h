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

#endif