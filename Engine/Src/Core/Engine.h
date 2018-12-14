#pragma once

#include <time.h>

#include "dllexp.h"

#include "Asset\Material.h"
#include "Asset\Mesh.h"
#include "Asset\Wave.h"
#include "Asset\Resource.h"

#include "Component\Script.h"
#include "Component\Collider.h"
#include "Component\Component.h"
#include "Component\Renderer.h"
#include "Component\Sound.h"
#include "Component\Transform.h"

#include "Input\KeyHandler.h"
#include "Input\Keys.h"

#include "Object\Object.h"
#include "Object\ObjectHandler.h"
#include "Object\Camera\Camera.h"
#include "Object\Camera\OrthographicCamera.h"
#include "Object\Camera\PerpectiveCamera.h"

#include "OpenGL\BufferGL.h"
#include "OpenGL\FrameGL.h"
#include "OpenGL\ObjectGL.h"
#include "OpenGL\PointGL.h"
#include "OpenGL\TextureGL.h"

#include "Physics\Boundary.h"
#include "Physics\CollisionListener.h"
#include "Physics\CollisionPhysics.h"
#include "Physics\PhysicsEngine.h"

#include "Scene\Scene.h"
#include "Util\ArrayList.h"
#include "includes\Reader.h"

class DLLDIR Engine {
public:
	static Engine * getInstance();
	void setFrame(FrameGL * frame);
	void setScene(Scene * scene);
	void startGame();
	Resource loadResource(ResourceType type, const char * filepath);
	Resource getResource(int resourceID);

	Object * _createObject();
	Object * _instantiate(Object * object);
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
	ObjectHandler * deleteList;
	ArrayList<Resource> * resourceList;
	
	int tickMax;
	int tickCount;
	clock_t tickNext;
	clock_t tickGap;
	clock_t initTime;
	clock_t lastTime;
	float lastDeltaTime;
	int lastFrameCount;
	int frameCount;
	int lastResourceID = 0;
};

// Engine makros
DLLDIR Object * createObject();
DLLDIR Object * instantiate(Object * object);
DLLDIR void removeObject(Object * object);
DLLDIR void setScreenSize(int x, int y);
DLLDIR float getDeltaTime();
DLLDIR int keyStatus(int key);
DLLDIR Scene * getScene(const char * sceneName);