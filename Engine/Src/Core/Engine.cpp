#ifndef ENGINE_CPP
#define ENGINE_CPP

#define _ENGINE_DEBUG

#include "Engine.h"
#include <stdio.h>

Engine::Engine() {
	tickMax = 50;

	this->objectHandler = new ObjectHandler();
	this->keyHandler = new KeyHandler();

	printf("Engine Initialized! \n");
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
	this->frame->setKeyHandler(this->keyHandler);
};

void Engine::setGame(Script * mainScript) {
	this->mainScript = mainScript;
}

void Engine::startGame() {
	printf("Engine Started! \n");

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
	if (this->frame != nullptr && x > 0 && y > 0) {
		this->frame->setSize(x, y);
	}
}

float Engine::_getDeltaTime() {
	return lastDeltaTime;
}

int Engine::_keyStatus(int key){	
	return keyHandler->getKeyStatus(key);
}

bool Engine::_isCollide(Object * object1, Object * object2) {
	Transform * t1 = object1->getComponent<Transform>();
	Transform * t2 = object2->getComponent<Transform>();

	// Lazy coding right??
	if (t1 != nullptr && t2 != nullptr) {
		float x1 = t1->getX();
		float y1 = t1->getY();
		float w1 = t1->getW();
		float h1 = t1->getH();

		float x2 = t2->getX();
		float y2 = t2->getY();
		float w2 = t2->getW();
		float h2 = t2->getH();

		bool xCollide = false;
		bool yCollide = false;

		if (x2 >= x1 && x2 <= x1 + w1)
			xCollide = true;
		if (x2 + w2 >= x1 && x2 + w2 <= x1 + w1)
			xCollide = true;
		if (y2 >= y1 && y2 <= y1 + w1)
			yCollide = true;
		if (y2 + w2 >= y1 && y2 + w2 <= y1 + w1)
			yCollide = true;

		if (xCollide && yCollide) {
			return true;
		}
	}

	return false;
}

void Engine::tick(int tickType) {
	
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
	
	Object ** list = this->objectHandler->getList();
	int size = this->objectHandler->getSize();

	int i;
	for (i = 0; i < size; i++) {
		
		if (list[i]->getComponent<Mesh>() != nullptr && list[i]->getComponent<Transform>() != nullptr) {
			frame->addObject(list[i]);
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

bool isCollide(Object * object1, Object * object2) {
	return Engine::getInstance()->_isCollide(object1, object2);
}
#endif // ENGINE_CPP