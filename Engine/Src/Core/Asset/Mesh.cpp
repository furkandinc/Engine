#include "Mesh.h"

Mesh::Mesh() {
	objectGL = nullptr;
	boundary = new Boundary();
}

void Mesh::setObjectGL(ObjectGL * objectGL) {
	if (this->objectGL != nullptr) {
		this->objectGL->dispose();
		free(this->objectGL);
	}

	this->objectGL = objectGL;
	float xmin = 0, xmax = 0, ymin = 0, ymax = 0, zmin = 0, zmax = 0; //what if mesh does not contain 0,0,0
	for (int i = 0; i < objectGL->getSize(); i++) {
		PointGL point = ((PointGL *)objectGL->getData())[i];
		vec4 pos = point.position;
		xmin = pos.x < xmin ? pos.x : xmin;
		xmax = pos.x > xmax ? pos.x : xmax;
		ymin = pos.y < ymin ? pos.y : ymin;
		ymax = pos.y > ymax ? pos.y : ymax;
		zmin = pos.z < zmin ? pos.z : zmin;
		zmax = pos.z > zmax ? pos.z : zmax;
	}

	boundary->setLeft(xmin);
	boundary->setRight(xmax);
	boundary->setTop(ymax);
	boundary->setBottom(ymin);
	boundary->setNear(zmax);
	boundary->setFar(zmin);
}

ObjectGL * Mesh::getObjectGL() {
	return objectGL;
}

Boundary * Mesh::getBoundary() {
	return boundary;
}

void * Mesh::generate() {
	Mesh * mesh = new Mesh();
	mesh->objectGL = (ObjectGL *)objectGL->generate();
	mesh->boundary = (Boundary *)boundary->generate();
	return mesh;
}

int Mesh::dispose() {
	objectGL->dispose();
	boundary->dispose();
	free(objectGL);
	free(boundary);
	return 0;
}