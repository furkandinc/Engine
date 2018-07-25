#ifndef FRAMEGL_H
#define FRAMEGL_H

#include "BufferGL.h"
#include "..\Object\Object.h"
#include "..\Input\KeyHandler.h"

class FrameGL {
public:
	
	void init(int argc, char ** argv, const char * title, int width, int height);
	void drawObject(Object * object);
	void setKeyHandler(KeyHandler * keyHandler);
	int getWidth();
	int getHeight();

	static FrameGL * getInstance();
private:
	char * title;
	int width;
	int height;
	KeyHandler * keyHandler;
	BufferGL * bufferGL;
	static FrameGL * frameInstance;

	FrameGL();
	void initBuffers();
	static void displayFunc();
	static void idleFunc();
	static void keyboardDownFunc(unsigned char key, int x, int y);
	static void keyboardUpFunc(unsigned char key, int x, int y);
	static void reshapeFunc(int w, int h);
};
#endif