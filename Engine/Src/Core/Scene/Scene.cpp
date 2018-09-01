#ifndef SCENE_CPP
#define SCENE_CPP

#include "Scene.h"

Scene::Scene() {
	this->objectHandler = new ObjectHandler();
}

void Scene::setName(const char * name){
	this->sceneName = name;
}

const char * Scene::getName() {
	return this->sceneName;
}

ObjectHandler * Scene::getObjectHandler() {
	return this->objectHandler;
}
#endif