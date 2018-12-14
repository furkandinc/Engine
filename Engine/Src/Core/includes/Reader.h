#pragma once

#include <stdio.h>
#include <vector>
#include "Angel.h"
#include "../OpenGL/PointGL.h"

bool readBMP(const char* filename, int * w, int * h, GLubyte ** image);
GLubyte *  readPPM(const char * filename, int * w, int * h);
bool readOBJ(const char * filename, PointGL ** pointGL, int * numVertex);