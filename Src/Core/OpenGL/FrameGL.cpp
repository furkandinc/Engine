#ifndef FRAMEGL_CPP
#define FRAMEGL_CPP

#include "FrameGL.h"

FrameGL::FrameGL(int argc, char ** argv, char * title, int width, int height) {
	this->title = title;
	this->width = width;
	this->height = height;

}

int FrameGL::getWidth() {
	return this->width;
}

int FrameGL::getHeight() {
	return this->height;
}

#endif