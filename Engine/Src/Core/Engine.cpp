#ifndef ENGINE_CPP
#define ENGINE_CPP

#define _ENGINE_DEBUG

#include <Engine.h>
#include <stdio.h>
#include <Object\Camera\Camera.h>
#include <Component\Control.h>

Engine::Engine() {
	tickMax = 100;

	this->keyHandler = new KeyHandler();
	this->physicsEngine = new PhysicsEngine();

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

void Engine::setScene(Scene * scene) {
	this->scene = scene;
	this->objectHandler = scene->getObjectHandler();
	this->physicsEngine->setObjectHandler(objectHandler);
	//frame->setTitle(scene->getName());
}

void Engine::startGame() {
	printf("Engine Started! \n");

	scene->initScene();

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
			tick(UPDATE);
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

Scene * Engine::_getScene(const char * sceneName) {
	return scene;
}

void Engine::tick(int tickType) {
	Object ** list = objectHandler->getList();
	for (int i = 0; i < objectHandler->getSize(); i++) {
		Object * object = list[i];
		Control * control = object->getComponent<Control>();
		if (control != nullptr) {
			Script * script = control->getScript();
			if (script != nullptr) {
				if (tickType == START) {
					script->onStart();
				}
				else if (tickType == UPDATE) {
					script->onUpdate();
				}
			}
		}
	}

	if (tickType == UPDATE) {
		if (this->keyHandler != nullptr) {
			this->keyHandler->tick();
		}
		physicsEngine->tick();
	}

	tickCount++;
}

void Engine::render() {
	
	Object ** list = this->objectHandler->getList();
	int size = this->objectHandler->getSize();

	int i;
	for (i = 0; i < size; i++) {
		Object * object = list[i];
		if (Camera * cam = dynamic_cast<Camera *>(object)) {
			frame->setCamera(cam);
		}
		Renderer * renderer = list[i]->getComponent<Renderer>();
		Transform * transform = list[i]->getComponent<Transform>();
		if (renderer != nullptr && transform != nullptr) {
			if(renderer->getMesh() != nullptr)
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

Scene * getScene(const char * sceneName) {
	return Engine::getInstance()->_getScene(sceneName);
}
#endif // ENGINE_CPP