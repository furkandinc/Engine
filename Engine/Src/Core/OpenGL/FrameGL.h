#ifndef FRAMEGL_H
#define FRAMEGL_H

#include "BufferGL.h"
#include "..\Object\Object.h"
#include "..\Input\KeyHandler.h"
#include "../Object/Camera/Camera.h"

class FrameGL {
public:
	
	void init(int argc, char ** argv, const char * title, int width, int height);
	void addObject(Object * object);
	void setKeyHandler(KeyHandler * keyHandler);
	int getWidth();
	int getHeight();
	void render();
	void setSize(int width, int height);
	void setCamera(Camera * camera);

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
	BufferGL * bufferGL;
	Camera * cam;
	static FrameGL * frameInstance;
	
	FrameGL();
	void initBuffers();
};
#endif