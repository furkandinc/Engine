#ifndef ENGINE_H
#define ENGINE_H

#include <time.h>

#include "Object\Object.h"
#include "Object\ObjectHandler.h"
#include "OpenGL\FrameGL.h"
#include "Logic\Script.h"
#include "Input\KeyHandler.h"

class Engine {
public:
	static Engine * getInstance();
	void setFrame(FrameGL * frame);
	void setGame(Script * mainScript);
	void startGame();

	Object * createObject();
	void removeObject(Object * object);
	void setScreenSize(int x, int y);
	float getDeltaTime();
	int keyStatus(int key);
	int isCollide(Object * object1, Object * object2);

private:
	Engine();
	void tick();
	void render();

	Script * mainScript;
	FrameGL * frame;
	static Engine * engineInstance;
	ObjectHandler * objectHandler;
	KeyHandler * keyHandler;

	int tickMax;
	int tickCount;
	clock_t tickNext;
	clock_t tickGap;
	clock_t initTime;
	clock_t lastTime;
	float lastDeltaTime;
};

// Engine makros
Object * createObject();
void removeObject(Object * object);
void setScreenSize(int x, int y);
float getDeltaTime();
int keyStatus(int key);
int isCollide(Object * object1, Object * object2);

Object * createObject() {
	return Engine::getInstance()->createObject();
}

void removeObject(Object * object) {
	Engine::getInstance()->removeObject(object);
}

void setScreenSize(int x, int y) {
	Engine::getInstance()->setScreenSize(x, y);
}

float getDeltaTime() {
	return Engine::getInstance()->getDeltaTime();
}

int keyStatus(int key) {
	return Engine::getInstance()->keyStatus(key);
}

int isCollide(Object * object1, Object * object2) {
	// TODO
	return 0;
}


#endif