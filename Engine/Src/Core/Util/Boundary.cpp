#ifndef BOUNDARY_CPP
#define BOUNDARY_CPP

#include "Boundary.h"

Boundary::Boundary() {
	red = 1;
	green = 1;
	blue = 1;
	alpha = 0;
	left = 0;
	right = 1;
	top = 1;
	bottom = 0;
	nearZ = 1;
	farZ = 0;

	cubeMesh();
}

void Boundary::setLeft(float left) {
	this->left = left;
	cubeMesh();
}

void Boundary::setRight(float right) {
	this->right = right;
	cubeMesh();
}

void Boundary::setTop(float top) {
	this->top = top;
	cubeMesh();
}

void Boundary::setBottom(float bottom) {
	this->bottom = bottom;
	cubeMesh();
}

void Boundary::setNear(float n) {
	this->nearZ = n;
	cubeMesh();
}

void Boundary::setFar(float f) {
	this->farZ = f;
	cubeMesh();
}

ObjectGL * Boundary::getObjectGL() {
	return objectGL;
}

void Boundary::cubeMesh() {
	PointGL pts[8];
	pts[0] = { vec4(left, bottom, farZ, 1), vec4(red, green, blue, alpha) };
	pts[1] = { vec4(left, top, farZ, 1), vec4(red, green, blue, alpha) };
	pts[2] = { vec4(right, top, farZ, 1), vec4(red, green, blue, alpha) };
	pts[3] = { vec4(right, bottom, farZ, 1), vec4(red, green, blue, alpha) };
	pts[4] = { vec4(left, bottom, nearZ, 1), vec4(red, green, blue, alpha) };
	pts[5] = { vec4(left, top, nearZ, 1), vec4(red, green, blue, alpha) };
	pts[6] = { vec4(right, top, nearZ, 1), vec4(red, green, blue, alpha) };
	pts[7] = { vec4(right, bottom, nearZ, 1), vec4(red, green, blue, alpha) };

	PointGL buffer[36];
	quad(buffer, 0, pts[0], pts[1], pts[2], pts[3]);
	quad(buffer, 6, pts[4], pts[5], pts[6], pts[7]);
	quad(buffer, 12, pts[0], pts[1], pts[5], pts[4]);
	quad(buffer, 18, pts[0], pts[4], pts[7], pts[3]);
	quad(buffer, 24, pts[1], pts[2], pts[6], pts[5]);
	quad(buffer, 30, pts[2], pts[3], pts[7], pts[6]);

	this->objectGL->setPoints(buffer, 36);
}

void Boundary::quad(PointGL * pointBuffer, int index, PointGL p1, PointGL p2, PointGL p3, PointGL p4) {
	pointBuffer[index] = p1;
	pointBuffer[index + 1] = p2;
	pointBuffer[index + 2] = p3;
	pointBuffer[index + 3] = p1;
	pointBuffer[index + 4] = p3;
	pointBuffer[index + 5] = p4;
}

#endif