#ifndef FRAMEGL_H
#define FRAMEGL_H

#include "..\includes\Angel.h"

class FrameGL {
public:
	FrameGL(int argc, char ** argv, char * title, int width, int height);
	int getWidth();
	int getHeight();
private:
	char * title;
	int width;
	int height;
};

#endif