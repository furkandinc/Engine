#ifndef ENGINE_CPP
#define ENGINE_CPP

#include "Engine.h"

Engine::Engine() {
	tickMax = 50;

	this->objectHandler = new ObjectHandler();
	this->keyHandler = new KeyHandler();
}

Engine *Engine::engineInstance = NULL;

Engine * Engine::getInstance() {
	if (engineInstance == 0) {
		engineInstance = new Engine();
	}

	return engineInstance;
}

void Engine::setFrame(FrameGL  * frame) {
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
	return keyHandler->getKeyStatus(key);
}

int Engine::isCollide(Object * object1, Object * object2) {
	// TODO
	return 0;
}

void Engine::tick() {
	// TODO
}

void Engine::render() {
	// TODO
}


#endif // ENGINE_CPP