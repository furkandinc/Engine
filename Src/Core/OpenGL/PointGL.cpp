#ifndef POINTGL_CPP
#define POINTGL_CPP

#include "PointGL.h"

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