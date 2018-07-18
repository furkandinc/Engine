#ifndef OBJECTHANDLER_CPP
#define OBJECTHANDLER_CPP

#include "ObjectHandler.h"

ObjectHandler::ObjectHandler() {
	this->list = (Object **)malloc(sizeof(Object *) * 10);
	this->count = 0;
	this->size = 10;
}

void ObjectHandler::add(Object * object) {
	if (indexOf(object) == -1) {
		checkSize();
		this->list[count++] = object;
	}
}

int ObjectHandler::indexOf(Object * object) {
	for (int i = 0; i < count; i++) {
		if (list[i] == object) {
			return i;
		}
	}
	return -1;
}

int ObjectHandler::getSize() {
	return count;
}

Object * ObjectHandler::remove(int index) {
	if (index < 0 || index >= count) {
		return nullptr;
	}

	Object * answer = list[index];

	for (int i = index; i < count; i++) {
		if (i != size - 1)
			list[i] = list[i + 1];
		else
			list[i] = nullptr;
	}

	return answer;
}

void ObjectHandler::checkSize() {
	if (size == count) {
		
		size *= 2;
		Object ** old = list;
		
		list = (Object **)malloc(sizeof(Object *) * size);

		for (int i = 0; i < count; i++) {
			list[i] = old[i];
		}
	}
}

#endif