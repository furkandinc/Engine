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
	renderer->setMaterial(new Material());
	addComponent(renderer);
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
	printf("component %d\n", componentListCount);
	obj->removeComponent(0);
	obj->removeComponent(0);
	for (int i = 0; i < componentListCount; i++) {
		printf("object:components %d\n", i);
		obj->addComponent((Component *)componentList[i]->generate());
		printf("object:components %d end\n", i);
	}
	for (int i = 0; i < childListCount; i++) {
		obj->addChild((Object *)childList[i]->generate());
	}
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