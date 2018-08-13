#ifndef ENGINE_CPP
#define ENGINE_CPP

#define _ENGINE_DEBUG

#include "Engine.h"
#include <stdio.h>

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
	tickNext = initTime + tickGap;
	frameCount = 0;

	clock_t debugNext = initTime + CLOCKS_PER_SEC;

	this->tick(START);

	while (true) {
		clock_t currentTime = clock();

		if (tickNext < currentTime) {
			this->tick(UPDATE);
			tickNext = tickNext + tickGap;
			lastDeltaTime = float(currentTime - lastTime) / CLOCKS_PER_SEC;
			lastTime = currentTime;
		}
		
		this-> render();

		if (debugNext < currentTime) {
#ifdef _ENGINE_DEBUG
			printf("Fps: %d, tps: %d\n", frameCount, tickCount);
#endif
			tickCount = 0;
			frameCount = 0;
			debugNext = currentTime + CLOCKS_PER_SEC;
		}
	}
}

Object * Engine::_createObject() {
	Object * object = new Object();
	objectHandler->add(object);
	return object;
}

void Engine::_removeObject(Object * object) {
	objectHandler->remove(objectHandler->indexOf(object));
}

void Engine::_setScreenSize(int x, int y) {
	// TODO
}

float Engine::_getDeltaTime() {
	return lastDeltaTime;
}

int Engine::_keyStatus(int key){	
	return keyHandler->getKeyStatus(key);
}

int Engine::_isCollide(Object * object1, Object * object2) {
	// TODO
	return 0;
}

void Engine::tick(int tickType) {
	// TODO
	
	if (tickType == START) {
		mainScript->onStart();
	}
	else if(tickType == UPDATE){
		if (this->keyHandler != nullptr) {
			this->keyHandler->tick();
		}
		mainScript->onUpdate();
	}

	tickCount++;
}

void Engine::render() {
	// TODO
	
	Object ** list = this->objectHandler->getList();
	int size = this->objectHandler->getSize();

	int i;
	for (i = 0; i < size; i++) {
		
		if (list[i]->getComponent<Mesh>() != nullptr) {
			frame->addObject(list[i]);
			printf("YOLO\n");
		}
	}

	frame->render();
	frameCount++;
}


Object * createObject() {
	return Engine::getInstance()->_createObject();
}

void removeObject(Object * object) {
	Engine::getInstance()->_removeObject(object);
}

void setScreenSize(int x, int y) {
	Engine::getInstance()->_setScreenSize(x, y);
}

float getDeltaTime() {
	return Engine::getInstance()->_getDeltaTime();
}

int keyStatus(int key) {
	return Engine::getInstance()->_keyStatus(key);
}

int isCollide(Object * object1, Object * object2) {
	// TODO
	return 0;
}
#endif // ENGINE_CPP