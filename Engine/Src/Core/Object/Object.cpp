#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "Object.h"
#include "../Asset/CubeMesh.h"
#include "../Component/Component.h"
#include "../Component/Transform.h"
#include "../Component/Renderer.h"

Object::Object() {
	childListSize = 5;
	childList = (Object **)malloc(sizeof(Object *) * childListSize);
	childListCount = 0;

	componentListSize = 5;
	componentList = (Component **)malloc(sizeof(Component *) * componentListSize);
	componentListCount = 0;
	
	parentObject = nullptr;

	addComponent(new Transform());
	Renderer * renderer = new Renderer();
	renderer->setMesh(new CubeMesh());
	addComponent(renderer);
};

void Object::addComponent(Component * component) {
	resizeBuffers();
	componentList[componentListCount] = component;
	componentListCount++;
	component->object = this;
};

Component * Object::removeComponent(int index) {
	if (index < 0 || index >= componentListCount) {
		return nullptr;
	}

	Component * answer = nullptr;
	for (int i = 0; i < componentListCount; i++) {
		if (i == componentListCount) {
			answer = componentList[i];
			componentList[i] = (Component *) nullptr;
		}
		else if (i >= index) {
			componentList[i] = componentList[i + 1];
		}
	}

	answer->object = nullptr;
	componentListCount--;
	return answer;
}

Object * Object::parent() {
	return parentObject;
}

Object ** Object::children() {
	return childList;
}

int Object::childCount() {
	return childListCount;
}

void Object::addChild(Object * object) {
	resizeBuffers();
	childList[childListCount] = object;
	childListCount++;
	object->parentObject = this;
}

Object * Object::removeChild(int index) {
	if (index < 0 || index >= childListCount) {
		return nullptr;
	}

	Object * answer = nullptr;
	for (int i = 0; i < childListCount; i++) {
		if (i == childListCount) {
			answer = childList[i];
			childList[i] = (Object *) nullptr;
		}
		else if (i >= index) {
			childList[i] = childList[i + 1];
		}
	}

	answer->parentObject = nullptr;
	childListCount--;
	return answer;
}

void Object::resizeBuffers() {
	if (childListSize == childListCount) {
		childListSize *= 2;
		Object ** newList = (Object **)malloc(sizeof(Object *) * childListSize);
		for (int i = 0; i < childListCount; i++) {
			newList[i] = childList[i];
		}
		free(childList);
		childList = newList;
	}

	if (componentListSize == componentListCount) {
		componentListSize *= 2;
		Component ** newList = (Component **)malloc(sizeof(Component *) * componentListSize);
		for (int i = 0; i < componentListCount; i++) {
			newList[i] = componentList[i];
		}
		free(componentList);
		componentList = newList;
	}
}

#endif