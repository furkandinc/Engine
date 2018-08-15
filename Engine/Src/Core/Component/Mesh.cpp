#ifndef MESH_CPP
#define MESH_CPP

#include <stdlib.h>
#include <stdio.h>
#include "Mesh.h"

Mesh::Mesh() {
	this->objectGL = new ObjectGL();

	red = 128;
	green = 128;
	blue = 128;

	squareMesh();
}

void Mesh::setColor(int r, int g, int b) {
	this->red = r;
	this->green = g;
	this->blue = b;
}

void Mesh::squareMesh() {
	PointGL pts[6];
	PointGL nokta1(0, 1, 0, 1, red, green, blue);
	PointGL nokta2(0, 0, 0, 1, red, green, blue);
	PointGL nokta3(1, 0, 0, 1, red, green, blue);
	PointGL nokta4(1, 0, 0, 1, red, green, blue);
	PointGL nokta5(1, 1, 0, 1, red, green, blue);
	PointGL nokta6(0, 1, 0, 1, red, green, blue);
	pts[0] = nokta1;
	pts[1] = nokta2;
	pts[2] = nokta3;
	pts[3] = nokta4;
	pts[4] = nokta5;
	pts[5] = nokta6;
	printf("Mesh:squaremesh\n");
	this->objectGL->setPoints(pts, 6);

}

ObjectGL * Mesh::getObjectGL() {
	return this->objectGL;
};
#endif