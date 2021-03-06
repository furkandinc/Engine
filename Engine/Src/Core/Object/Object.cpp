#include "Object.h"
#include "../Component/Component.h"
#include "../Component/Transform.h"
#include "../Component/Renderer.h"

Object::Object() {
	tag = "Tag";

	childListSize = 5;
	childList = (Object **)malloc(sizeof(Object *) * childListSize);
	childListCount = 0;

	componentListSize = 5;
	componentList = (Component **)malloc(sizeof(Component *) * componentListSize);
	componentListCount = 0;
	
	parentObject = nullptr;

	addComponent(new Transform());
};

void Object::addComponent(Component * component) {
	resizeBuffers();
	componentList[componentListCount] = component;
	componentListCount++;
	component->object = this;
};

bool Object::removeComponent(int index) {
	if (index < 0 || index >= componentListCount) {
		return false;
	}

	for (int i = index; i < componentListCount; i++) {
		if (i != componentListSize - 1)
			componentList[i] = componentList[i + 1];
		else
			componentList[i] = nullptr;
	}

	componentListCount--;
	return true;
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

void Object::abstraction() {

}

void * Object::generate() {
	Object * obj = new Object();
	obj->removeComponent(0); //initialized Transform
	for (int i = 0; i < componentListCount; i++) {
		obj->addComponent((Component *)componentList[i]->generate());
	}
	for (int i = 0; i < childListCount; i++) {
		obj->addChild((Object *)childList[i]->generate());
	}
	obj->tag = tag;
	return obj;
}

int Object::dispose() {
	for (int i = 0; i < componentListCount; i++) {
		componentList[i]->dispose();
		free(componentList[i]);
	}
	for (int i = 0; i < childListCount; i++) {
		childList[i]->dispose();
		free(childList[i]);
	}
	free(componentList);
	free(childList);

	return 0;
}

void Object::setTag(const char * tag) {
	this->tag = tag;
}

const char * Object::getTag() {
	return tag;
}