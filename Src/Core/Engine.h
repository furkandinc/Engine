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

	Object * _createObject();
	void _removeObject(Object * object);
	void _setScreenSize(int x, int y);
	float _getDeltaTime();
	int _keyStatus(int key);
	int _isCollide(Object * object1, Object * object2);

private:
	Engine();
	void tick(int tickType);
	void render();
	static enum tickType : int {START, UPDATE};

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
	int lastFrameCount;
	int frameCount;
};

// Engine makros
Object * createObject();
void removeObject(Object * object);
void setScreenSize(int x, int y);
float getDeltaTime();
int keyStatus(int key);
int isCollide(Object * object1, Object * object2);



#endif