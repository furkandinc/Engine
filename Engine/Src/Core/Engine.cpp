#ifndef ENGINE_CPP
#define ENGINE_CPP

#define _ENGINE_DEBUG

#include <Engine.h>
#include <stdio.h>
#include "lodepng.h"

Engine::Engine() {
	tickMax = 100;

	this->keyHandler = new KeyHandler();
	this->physicsEngine = new PhysicsEngine();
	this->deleteList = new ObjectHandler();
	this->resourceList = new ArrayList<Resource>();

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
	printf("Engine Started!\n");

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

Resource Engine::loadResource(ResourceType type, const char * filepath) {
	Resource rsc;
	if (type == OBJTYPE) {
		PointGL * points;
		int numVertex;
		bool result = readOBJ(filepath, &points, &numVertex);
		rsc.data = (void *)points;
		rsc.size = numVertex;
		rsc.unitsize = sizeof(PointGL);
		rsc.argc = 0;
		rsc.argv = nullptr;
	}
	else if (type == BMPTYPE) {
		int w;
		int h;
		GLubyte * data;
		bool result = readBMP(filepath, &w, &h, &data);
		int * argv = (int *)malloc(sizeof(int) * 2);
		argv[0] = w;
		argv[1] = h;
		rsc.data = (void *)data;
		rsc.size = w * h * 4;
		rsc.unitsize = sizeof(GLubyte);
		rsc.argc = 2;
		rsc.argv = (void *)argv;
	}
	else if (type == PNGTYPE) {
		std::vector<GLubyte> * image = new std::vector<GLubyte>();
		unsigned width, height;
		unsigned error = lodepng::decode((*image), width, height, filepath);
		if (error)
			std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		
		// upside down the rows
		int width_size = width * 4;
		for (int i = 0; i < height / 2; i++) {
			for (int j = 0; j < width_size ; j++) {
				unsigned temp = (*image)[i * width_size + j];
				(*image)[i * width_size + j] = (*image)[(height - i - 1) * width_size + j];
				(*image)[(height - i - 1) * width_size + j] = temp;
			}
		}

		int * argv = (int *)malloc(sizeof(int) * 2);
		argv[0] = width;
		argv[1] = height;
		rsc.data = &(* image)[0];
		rsc.size = width * height * 4;
		rsc.unitsize = sizeof(GLubyte);
		rsc.argc = 2;
		rsc.argv = argv;
	}

	rsc.resourceid = ++lastResourceID;
	rsc.resourcetype = type;
	resourceList->add(rsc);
	return rsc;
}

Resource Engine::getResource(int id) {
	Resource ans;
	for (int i = 0; i < resourceList->getCount(); i++) {
		Resource temp = resourceList->get(i);
		if (temp.resourceid == id) {
			return temp;
		}
	}
	return ans;
}

Object * Engine::_createObject() {
	Object * object = new Object();
	objectHandler->add(object);

	return object;
}

Object * Engine::_instantiate(Object * object) {
	Object * obj = (Object *)(object->generate());
	objectHandler->add(obj);
	return obj;
}

void Engine::_removeObject(Object * object) {
	deleteList->add(object);
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
		Script * script = object->getComponent<Script>();
		if (script != nullptr) {
			if (tickType == START) {
				script->onStart();
			}
			else if (tickType == UPDATE) {
				script->onUpdate();
			}
		}
	}
	if (tickType == UPDATE) {
		if (this->keyHandler != nullptr) {
			this->keyHandler->tick();
		}
		physicsEngine->tick();
		Object ** objDestroy = deleteList->getList();
		for (int i = 0; i < deleteList->getSize(); i++) {
			Object * object = objDestroy[deleteList->getSize() - 1];
			objectHandler->remove(object);
			frame->removeObject(object);
			object->dispose();
			free(object);
			deleteList->remove(object);
		}
		
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
			if (renderer->getMesh() != nullptr) {
				frame->addObject(list[i]);
			}
		}
	}
	
	frame->render();
	frameCount++;
}


Object * createObject() {
	return Engine::getInstance()->_createObject();
}

Object * instantiate(Object * object) {
	return Engine::getInstance()->_instantiate(object);
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