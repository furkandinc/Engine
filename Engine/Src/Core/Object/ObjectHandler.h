#ifndef OBJECT_HANDLER_H
#define OBJECT_HANDLER_H


#include <stdlib.h>

#include "Object.h"

class ObjectHandler {
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

#endif