#ifndef MESH_H
#define MESH_H

#include "Component.cpp"

#include <stdlib.h>

#include "..\OpenGL\PointGL.cpp"
#include "..\OpenGL\Renderable.cpp"
#include "..\OpenGL\ObjectGL.cpp"

#endif

class Mesh : public Component, Renderable {
public:
	Mesh();
	void setColor(int r, int g, int b);

	ObjectGL * getObjectGL();

private:
	void squareMesh();

	int red, green, blue;

	ObjectGL * objectGL;
};

Mesh::Mesh() {
	objectGL = new ObjectGL();

	red = 128;
	green = 128;
	blue = 128;

	squareMesh();
}

void Mesh::setColor(int r, int g, int b) {
	this->red = r;
	this->green = g;
	this->blue = b;
	squareMesh();
}

void Mesh::squareMesh() {
	PointGL ** points = (PointGL **)malloc(sizeof(PointGL * ) * 6);
	PointGL nokta1(0, 1, 0, 1, red, green, blue);
	PointGL nokta2(0, 0, 0, 1, red, green, blue);
	PointGL nokta3(1, 0, 0, 1, red, green, blue);
	PointGL nokta4(1, 0, 0, 1, red, green, blue);
	PointGL nokta5(1, 1, 0, 1, red, green, blue);
	PointGL nokta6(0, 1, 0, 1, red, green, blue);
	points[0] = &nokta1;
	points[1] = &nokta2;
	points[2] = &nokta3;
	points[3] = &nokta4;
	points[4] = &nokta5;
	points[5] = &nokta6;

	objectGL->setPoints(points, 6);
}