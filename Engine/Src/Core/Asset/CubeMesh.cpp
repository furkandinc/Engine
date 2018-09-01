#ifndef CUBEMESH_CPP
#define CUBEMESH_CPP

#include "CubeMesh.h"

CubeMesh::CubeMesh() {
	objectGL = new ObjectGL();
	boundary = new Boundary();
	boundary->setBottom(-0.5);
	boundary->setTop(0.5);
	boundary->setLeft(-0.5);
	boundary->setRight(0.5);
	boundary->setNear(0.5);
	boundary->setFar(-0.5);

	cubeMesh();
}

void CubeMesh::cubeMesh() {
	vec4 pts[8];
	
	mat4 ori = Translate(vec3(-0.5, -0.5, -0.5));
	pts[0] = ori * vec4(0, 0, 0, 1);
	pts[1] = ori * vec4(0, 1, 0, 1);
	pts[2] = ori * vec4(1, 1, 0, 1);
	pts[3] = ori * vec4(1, 0, 0, 1);
	pts[4] = ori * vec4(0, 0, 1, 1);
	pts[5] = ori * vec4(0, 1, 1, 1);
	pts[6] = ori * vec4(1, 1, 1, 1);
	pts[7] = ori * vec4(1, 0, 1, 1);

	vec3 norm[6];
	norm[0] = vec3(0, 0, -1);
	norm[1] = vec3(0, 0, 1);
	norm[2] = vec3(-1, 0, 0);
	norm[3] = vec3(0, -1, 0);
	norm[4] = vec3(0, 1, 0);
	norm[5] = vec3(1, 0, 0);

	PointGL buffer[36];
	quad(buffer, 0, pts[0], pts[1], pts[2], pts[3], norm[0]);
	quad(buffer, 6, pts[4], pts[5], pts[6], pts[7], norm[1]);
	quad(buffer, 12, pts[0], pts[1], pts[5], pts[4], norm[2]);
	quad(buffer, 18, pts[0], pts[4], pts[7], pts[3], norm[3]);
	quad(buffer, 24, pts[1], pts[2], pts[6], pts[5], norm[4]);
	quad(buffer, 30, pts[2], pts[3], pts[7], pts[6], norm[5]);

	this->objectGL->setPoints(buffer, 36);
}

void CubeMesh::quad(PointGL * pointBuffer, int index, vec4 p1, vec4 p2, vec4 p3, vec4 p4, vec3 normal) {
	pointBuffer[index] = PointGL({ p1, normal, vec2(0, 0)});
	pointBuffer[index + 1] = PointGL({ p2, normal, vec2(1, 0) });
	pointBuffer[index + 2] = PointGL({ p3, normal, vec2(1,1) });
	pointBuffer[index + 3] = PointGL({ p1, normal, vec2(0,0) });
	pointBuffer[index + 4] = PointGL({ p3, normal, vec2(1,1) });
	pointBuffer[index + 5] = PointGL({ p4, normal, vec2(0,1) });
}

ObjectGL * CubeMesh::getObjectGL() {
	return this->objectGL;
};

Boundary * CubeMesh::getBoundary() {
	return boundary;
}
#endif