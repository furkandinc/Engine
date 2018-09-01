#ifndef ENGINE_H
#define ENGINE_H

#include <time.h>

#include "Object\Object.h"
#include "Object\ObjectHandler.h"
#include "OpenGL\FrameGL.h"
#include "Asset\Script.h"
#include "Input\KeyHandler.h"
#include "Physics\PhysicsEngine.h"
#include "Scene\Scene.h"

class Engine {
public:
	static Engine * getInstance();
	void setFrame(FrameGL * frame);
	void setScene(Scene * scene);
	void startGame();

	Object * _createObject();
	void _removeObject(Object * object);
	void _setScreenSize(int x, int y);
	float _getDeltaTime();
	int _keyStatus(int key);
	Scene * _getScene(const char * sceneName);

private:
	Engine();
	void tick(int tickType);
	void render();
	static enum tickType : int {START, UPDATE};

	Scene * scene;
	FrameGL * frame;
	static Engine * engineInstance;
	ObjectHandler * objectHandler;
	KeyHandler * keyHandler;
	PhysicsEngine * physicsEngine;
	
	int tickMax;
	int tickCount;
	clock_t tickNext;
	clock_t tickGap;
	clock_t initTime;
	clock_t lastTime;
	float lastDeltaTime;
	int lastFrameCount;
	int frameCount;
};

// Engine makros
Object * createObject();
void removeObject(Object * object);
void setScreenSize(int x, int y);
float getDeltaTime();
int keyStatus(int key);
Scene * getScene(const char * sceneName);

#endif