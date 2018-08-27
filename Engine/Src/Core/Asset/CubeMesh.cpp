#ifndef CUBEMESH_CPP
#define CUBEMESH_CPP

#include "CubeMesh.h"

CubeMesh::CubeMesh() {
	this->objectGL = new ObjectGL();

	red = 0.5;
	green = 0.5;
	blue = 0.5;
	alpha = 1;

	cubeMesh();
}

void CubeMesh::setColor(int r, int g, int b) {
	this->red = r / 255.0;
	this->green = g / 255.0;
	this->blue = b / 255.0;
	this->alpha = 1.0;

	cubeMesh();
}

void CubeMesh::cubeMesh() {
	PointGL pts[8];
	pts[0] = { vec4(0, 0, 0, 1), vec4(red, green, blue, alpha) };
	pts[1] = { vec4(0, 1, 0, 1), vec4(red, green, blue, alpha) };
	pts[2] = { vec4(1, 1, 0, 1), vec4(red, green, blue, alpha) };
	pts[3] = { vec4(1, 0, 0, 1), vec4(red, green, blue, alpha) };
	pts[4] = { vec4(0, 0, 1, 1), vec4(red, green, blue, alpha) };
	pts[5] = { vec4(0, 1, 1, 1), vec4(red, green, blue, alpha) };
	pts[6] = { vec4(1, 1, 1, 1), vec4(red, green, blue, alpha) };
	pts[7] = { vec4(1, 0, 1, 1), vec4(red, green, blue, alpha) };

	PointGL buffer[36];
	quad(buffer, 0, pts[0], pts[1], pts[2], pts[3]);
	quad(buffer, 6, pts[4], pts[5], pts[6], pts[7]);
	quad(buffer, 12, pts[0], pts[1], pts[5], pts[4]);
	quad(buffer, 18, pts[0], pts[4], pts[7], pts[3]);
	quad(buffer, 24, pts[1], pts[2], pts[6], pts[5]);
	quad(buffer, 30, pts[2], pts[3], pts[7], pts[6]);

	this->objectGL->setPoints(buffer, 36);
}

void CubeMesh::quad(PointGL * pointBuffer, int index, PointGL p1, PointGL p2, PointGL p3, PointGL p4) {
	pointBuffer[index] = p1;
	pointBuffer[index + 1] = p2;
	pointBuffer[index + 2] = p3;
	pointBuffer[index + 3] = p1;
	pointBuffer[index + 4] = p3;
	pointBuffer[index + 5] = p4;
}

ObjectGL * CubeMesh::getObjectGL() {
	return this->objectGL;
};

Boundary * CubeMesh::getBoundary() {
	return nullptr;
}
#endif