#ifndef POINTGL_H
#define POINTGL_H

class PointGL {
	float x, y, z, w;
	float r, g, b, a;
public:
	PointGL(float x, float y, float z, int r, int g, int b, int a);
};

#endif