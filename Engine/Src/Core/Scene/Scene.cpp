#ifndef SCENE_CPP
#define SCENE_CPP

#include "Scene.h"

Scene::Scene(const char * name) {
	this->sceneName = name;
	this->objectHandler = new ObjectHandler();
}

const char * Scene::getName() {
	return this->sceneName;
}

ObjectHandler * Scene::getObjectHandler() {
	return this->objectHandler;
}
#endif