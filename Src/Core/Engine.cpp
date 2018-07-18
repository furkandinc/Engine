#ifndef ENGINE_H
#define ENGINE_H

#include <time.h>

#include "Object\Object.cpp"
#include "Object\ObjectHandler.cpp"
#include "OpenGL\Frame.cpp"
#include "Logic\Script.cpp"


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
	Engine::getInstance()->getDeltaTime();
}

int keyStatus(int key) {
	Engine::getInstance()->keyStatus(key);
}

int isCollide(Object * object1, Object * object2) {

}

#endif // ENGINE_H

class Engine {
public:
	static Engine * getInstance();
	void setFrame(Frame * frame);
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
	Frame * frame;
	static Engine * instance;
	ObjectHandler * objectHandler;

	int tickMax;
	int tickCount;
	clock_t tickNext;
	clock_t tickGap;
	clock_t initTime;
	clock_t lastTime;
	float lastDeltaTime;
};

Engine::Engine() {
	tickMax = 50;

	this->objectHandler = new ObjectHandler();
}

Engine * Engine::getInstance() {
	if (instance == nullptr) {
		instance = new Engine();
	}

	return instance;
}

void Engine::setFrame(Frame  * frame) {
	this->frame = frame;
};

void Engine::setGame(Script * mainScript) {
	this->mainScript = mainScript;
}

void Engine::startGame() {
	initTime = clock();
	lastTime = initTime;
	tickCount = 0;
	tickGap = (1.0 / tickMax) * CLOCKS_PER_SEC;
	tickNext = lastTime + tickGap;

	mainScript->onStart();

	while (true) {
		clock_t currentTime = clock();
		lastDeltaTime = float(currentTime - lastTime) / CLOCKS_PER_SEC;
		lastTime = currentTime;

		if (tickNext < currentTime) {
			this->tick();

			tickNext = tickNext + tickGap;
		}
		this-> render();
	}
}

Object * Engine::createObject() {
	Object * object = new Object();
	objectHandler->add(object);
	return object;
}

void Engine::removeObject(Object * object) {
	objectHandler->remove(objectHandler->indexOf(object));
}

void Engine::setScreenSize(int x, int y) {
	// TODO
}

float Engine::getDeltaTime() {
	return lastDeltaTime;
}

int Engine::keyStatus(int key){	
	//TODO
	return 0;
}

int Engine::isCollide(Object * object1, Object * object2) {
	// TODO
	return 0;
}

void Engine::tick() {
	
}

void Engine::render() {

}