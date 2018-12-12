#include "ObjectHandler.h"

ObjectHandler::ObjectHandler() {
	this->count = 0;
	this->size = 128;
	this->list = (Object **)malloc(sizeof(Object *) * this->size);
}

void ObjectHandler::add(Object * object) {
	checkSize();
	if (indexOf(object) == -1) {
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

	count--;

	return answer;
}

Object * ObjectHandler::remove(Object * object) {
	int result = indexOf(object);
	return remove(result);
}

void ObjectHandler::checkSize() {
	if (size == count) {
		size *= 2;
		
		Object ** tempData = (Object **)malloc(sizeof(Object *) * size);
		
		int i;
		for (i = 0; i < count; i++) {
			tempData[i] = list[i];
		}

		free(list);
		list = tempData;
	}
}

Object ** ObjectHandler::getList() {
	return list;
}