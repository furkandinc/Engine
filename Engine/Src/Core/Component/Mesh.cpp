#ifndef MESH_CPP
#define MESH_CPP

#include <stdlib.h>
#include <stdio.h>
#include "Mesh.h"

Mesh::Mesh() {
	this->objectGL = new ObjectGL();

	red = 0.5;
	green = 0.5;
	blue = 0.5;
	alpha = 1;

	squareMesh();
}

void Mesh::setColor(int r, int g, int b) {
	this->red = r/255.0;
	this->green = g/255.0;
	this->blue = b/255.0;
	this->alpha = 1.0;
}

void Mesh::squareMesh() {
	printf("Mesh:squaremesh\n");
	PointGL pts[6];
	pts[0] = { vec4(0, 1, 0, 1), vec4(red, green, blue, alpha) };
	pts[1] = { vec4(0, 0, 0, 1), vec4(red, green, blue, alpha) };
	pts[2] = { vec4(1, 0, 0, 1), vec4(red, green, blue, alpha) };
	pts[3] = { vec4(1, 0, 0, 1), vec4(red, green, blue, alpha) };
	pts[4] = { vec4(1, 1, 0, 1), vec4(red, green, blue, alpha) };
	pts[5] = { vec4(0, 1, 0, 1), vec4(red, green, blue, alpha) };

	this->objectGL->setPoints(pts, 6);

}

ObjectGL * Mesh::getObjectGL() {
	return this->objectGL;
};
#endif