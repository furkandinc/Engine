#ifndef POINTGL_CPP
#define POINTGL_CPP

#include "PointGL.h"

PointGL::PointGL(void) {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

PointGL::PointGL(float x, float y, float z, int r, int g, int b, int a) {
	this->x = x;
	this->y = y;
	this->z= z;
	this->w = 1;
	this->r = r / (float) 255;
	this->g= g / (float) 255;
	this->b = b / (float) 255;
	this->a= a / (float) 255;
}

#endif