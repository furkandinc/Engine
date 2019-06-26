#pragma once

#include "BufferGL.h"
#include "../dllexp.h"
#include "../Object/Object.h"
#include "../Input/KeyHandler.h"
#include "../Object/Camera/Camera.h"
#include "../Object/ObjectHandler.h"
#include "../Asset/Font.h"
#include "../Component/UIText.h"

class DLLDIR FrameGL {
public:
	
	void init(int argc, char ** argv, const char * title, int width, int height);
	void addObject(Object * object);
	void removeObject(Object * object);
	void addUIObject(Object * object);
	void removeUIObject(Object * object);
	void setKeyHandler(KeyHandler * keyHandler);
	void loadFont(Font font);
	//void setObjectHandler(ObjectHandler * objectHandler);
	int getWidth();
	int getHeight();
	void render();
	void setSize(int width, int height);
	void setCamera(Camera * camera);
	void loadingScene();

	static FrameGL * getInstance();

	static void displayFunc();
	static void idleFunc();
	static void keyboardDownFunc(unsigned char key, int x, int y);
	static void keyboardUpFunc(unsigned char key, int x, int y);
	static void specialDownFunc(int key, int x, int y);
	static void specialUpFunc(int key, int x, int y);
	static void reshapeFunc(int w, int h);

private:
	char * title;
	int width;
	int height;
	KeyHandler * keyHandler;
	//BufferGL * bufferGL;
	Camera * cam;
	ObjectHandler * objectHandler;
	ObjectHandler * uiObjectHandler;
	static FrameGL * frameInstance;
	
	FrameGL();
	void initBuffers();
	void static renderObj();
	void static renderUI();
};