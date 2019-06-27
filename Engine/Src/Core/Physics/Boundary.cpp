#include "Boundary.h"

Boundary::Boundary() {
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
	nearZ = 0;
	farZ = 0;
}

void Boundary::setLeft(float left) {
	this->left = left;
}

void Boundary::setRight(float right) {
	this->right = right;
}

void Boundary::setTop(float top) {
	this->top = top;
}

void Boundary::setBottom(float bottom) {
	this->bottom = bottom;
}

void Boundary::setNear(float n) {
	this->nearZ = n;
}

void Boundary::setFar(float f) {
	this->farZ = f;
}

void Boundary::setTransform(Transform * transform) {
	this->transform = transform;
}

bool inside(float x, float y, float z, float * bound) {
	if (x >= bound[0] && x <= bound[1] &&
		y >= bound[2] && y <= bound[3] &&
		z >= bound[4] && z <= bound[5]) {
		return true;
	}
	return false;
}

bool Boundary::collide(Boundary * boundary) {
	if (this->transform == nullptr && boundary->transform == nullptr)
		return false;

	float * a = this->generateBound();
	float * b = boundary->generateBound();

	if (inside(a[0], a[2], a[4], b) ||
		inside(a[0], a[2], a[5], b) ||
		inside(a[0], a[3], a[4], b) ||
		inside(a[0], a[3], a[5], b) ||
		inside(a[1], a[2], a[4], b) ||
		inside(a[1], a[2], a[5], b) ||
		inside(a[1], a[3], a[4], b) ||
		inside(a[1], a[3], a[5], b)) {
		free(a);
		free(b);
		return true;
	}

	if (inside(b[0], b[2], b[4], a) ||
		inside(b[0], b[2], b[5], a) ||
		inside(b[0], b[3], b[4], a) ||
		inside(b[0], b[3], b[5], a) ||
		inside(b[1], b[2], b[4], a) ||
		inside(b[1], b[2], b[5], a) ||
		inside(b[1], b[3], b[4], a) ||
		inside(b[1], b[3], b[5], a)) {
		free(a);
		free(b);
		return true;
	}

	return false;
}

float * Boundary::generateBound() {
	mat4 mat = transform->generateMatrix();

	vec4 ltn = mat * vec4(left, top, nearZ);
	vec4 ltf = mat * vec4(left, top, farZ);
	vec4 lbn = mat * vec4(left, bottom, nearZ);
	vec4 lbf = mat * vec4(left, bottom, farZ);
	vec4 rtn = mat * vec4(right, top, nearZ);
	vec4 rtf = mat * vec4(right, top, farZ);
	vec4 rbn = mat * vec4(right, bottom, nearZ);
	vec4 rbf = mat * vec4(right, bottom, farZ);

	vec4 temp[] = { ltn, ltf, lbn, lbf, rtn, rtf, rbn, rbf };
	float xmin=0, xmax = 0, ymin = 0, ymax = 0, zmin = 0, zmax = 0;

	for (int i = 0; i < 8; i++) {
		xmin = temp[i].x < xmin ? temp[i].x : xmin;
		xmax = temp[i].x > xmax ? temp[i].x : xmax;
		ymin = temp[i].y < ymin ? temp[i].y : ymin;
		ymax = temp[i].y > ymax ? temp[i].y : ymax;
		zmin = temp[i].z < zmin ? temp[i].z : zmin;
		zmax = temp[i].z > zmax ? temp[i].z : zmax;
	}
	
	float * ans = (float *)malloc(sizeof(float) * 6);
	ans[0] = xmin;
	ans[1] = xmax;
	ans[2] = ymin;
	ans[3] = ymax;
	ans[4] = zmin;
	ans[5] = zmax;

	return ans;
}

void * Boundary::generate() {
	Boundary * bd = new Boundary();
	bd->left = left;
	bd->right = right;
	bd->top = top;
	bd->bottom = bottom;
	bd->nearZ = nearZ;
	bd->farZ = farZ;
	bd->transform = transform;

	return bd;
}

int Boundary::dispose() {
	return 0;
}