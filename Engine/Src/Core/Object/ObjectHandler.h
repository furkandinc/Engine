#pragma once

#include <stdlib.h>

#include "Object.h"
#include "../dllexp.h"

class DLLDIR ObjectHandler {
public:

	ObjectHandler();

	void add(Object * object);
	int indexOf(Object * object);
	int getSize();
	Object * remove(int index);
	Object * remove(Object * object);
	Object ** getList();

private:

	Object ** list;
	int count;
	int size;

	void checkSize();
};