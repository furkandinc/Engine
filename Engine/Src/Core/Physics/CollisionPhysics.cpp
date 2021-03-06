#ifndef COLLISION_PHYSICS_CPP
#define COLLISION_PHYSICS_CPP

#include "CollisionPhysics.h"

bool isCollide(vec3 P0, vec3 P1, vec3 P2, vec3 rayStart, vec3 rayEnd) {
	//based on https://en.wikipedia.org/wiki/Line�plane_intersection
	float t, u, v;
	vec3 Ia = rayStart;
	vec3 Ib = rayEnd;
	vec3 Iab = Ib - Ia;
	vec3 P01 = P1 - P0;
	vec3 P02 = P2 - P0;

	float detResult = dot((-Iab), cross(P01, P02));
	if (detResult == 0) {
		//TODO check if ray is in the triangle
		return false;
	}

	t = dot(cross(P01, P02), Ia - P0) / dot(-Iab, cross(P01, P02));
	u = dot(cross(P02, -Iab), Ia - P0) / dot(-Iab, cross(P01, P02));
	v = dot(cross(-Iab, P01), Ia - P0) / dot(-Iab, cross(P01, P02));

	if (t >= 0 && t <= 1) {
		if (u >= 0 && u <= 1) {
			if (v >= 0 && v <= 1) {
				if (u + v >= 0 && u + v <= 1) {
					return true;
				}
			}
		}
	}

	return false;
}

bool isCollide(vec3 a1, vec3 a2, vec3 a3, vec3 b1, vec3 b2, vec3 b3) {
	if (isCollide(a1, a2, a3, b1, b2))
		return true;
	if (isCollide(a1, a2, a3, b2, b3))
		return true;
	if (isCollide(a1, a2, a3, b3, b1))
		return true;
	if (isCollide(b1, b2, b3, a1, a2))
		return true;
	if (isCollide(b1, b2, b3, a2, a3))
		return true;
	if (isCollide(b1, b2, b3, a3, a1))
		return true;
	return false;
}

bool isCollide(ObjectGL * b1, Transform * t1, ObjectGL * b2, Transform * t2) {
	PointGL * points1 = b1->getData();
	PointGL * points2 = b2->getData();
	mat4 matrice1 = t1->generateMatrix();
	mat4 matrice2 = t2->generateMatrix();
	for (int i = 0; i < b1->getSize(); i += 3) {
		for (int j = 0; j < b2->getSize(); j += 3) {

			vec4 a1 = matrice1 * points1[i].position;
			vec4 a2 = matrice1 * points1[i + 1].position;
			vec4 a3 = matrice1 * points1[i + 2].position;
			vec4 b1 = matrice2 * points2[j].position;
			vec4 b2 = matrice2 * points2[j + 1].position;
			vec4 b3 = matrice2 * points2[j + 2].position;

			bool result = isCollide(
				vec3(a1.x, a1.y, a1.z),
				vec3(a2.x, a2.y, a2.z),
				vec3(a3.x, a3.y, a3.z),
				vec3(b1.x, b1.y, b1.z),
				vec3(b2.x, b2.y, b2.z),
				vec3(b3.x, b3.y, b3.z)
			);
			if (result) {
				return true;
			}
		}
	}

	return false;
}

bool isCollide(Mesh * mesh1, Transform * t1, Mesh * mesh2, Transform * t2) {
	Boundary * boundary1 = mesh1->getBoundary();
	Boundary * boundary2 = mesh2->getBoundary();
	
	boundary1->setTransform(t1);
	boundary2->setTransform(t2);

	bool result = false;
	bool bound = boundary1->collide(boundary2);

	if (bound) {
		result = isCollide(mesh1->getObjectGL(), t1, mesh2->getObjectGL(), t2);
	}

	return result;
}

bool isCollide(Object * object1, Object * object2) {
	Collider * collider1 = object1->getComponent<Collider>();
	Collider * collider2 = object2->getComponent<Collider>();

	if (collider1 == nullptr || collider2 == nullptr)
		return false;

	if (!collider1->getCollidable() || !collider2->getCollidable())
		return false;

	Mesh * mesh1 = collider1->getMesh();
	Mesh * mesh2 = collider2->getMesh();

	if (mesh1 == nullptr || mesh2 == nullptr)
		return false;

	Transform * transform1 = object1->getComponent<Transform>();
	Transform * transform2 = object2->getComponent<Transform>();

	if (transform1 == nullptr || transform2 == nullptr)
		return false;

	return isCollide(mesh1, transform1, mesh2, transform2);
}


#endif