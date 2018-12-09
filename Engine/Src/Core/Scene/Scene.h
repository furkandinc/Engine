#pragma once

#include "..\dllexp.h"
#include "..\Object\ObjectHandler.h"

class DLLDIR Scene {
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