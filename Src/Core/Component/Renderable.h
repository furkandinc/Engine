#ifndef RENDERABLE_H

#include "..\OpenGL\ObjectGL.h"

class Renderable {
public:
	virtual ObjectGL * getObjectGL() = 0;
};

#endif