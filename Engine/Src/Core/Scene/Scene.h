#ifndef SCENE_H
#define SCENE_H

#include "..\Object\ObjectHandler.h"

class Scene {
public:
	Scene();
	virtual void initScene() = 0;
	void setName(const char * name);
	const char * getName();
	ObjectHandler * getObjectHandler();

protected:
	const char * sceneName;
	ObjectHandler * objectHandler;
};

#endif