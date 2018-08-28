#ifndef COLLISION_PHYSICS_H
#define COLLISION_PHYSICS_H

#include "Boundary.h"
#include "../OpenGL/ObjectGL.h"
#include "../Object/Object.h"
#include "../Component/Transform.h"
#include "../Asset/Mesh.h"
#include "../Component/Collider.h"

bool isCollide(vec3 P0, vec3 P1, vec3 P2, vec3 rayStart, vec3 rayEnd);

bool isCollide(vec3 a1, vec3 a2, vec3 a3, vec3 b1, vec3 b2, vec3 b3);

bool isCollide(ObjectGL * b1, Transform * t1, ObjectGL * b2, Transform * t2);

bool isCollide(Mesh * mesh1, Transform * t1, Mesh * mesh2, Transform * t2);

bool isCollide(Object * object1, Object * object2);

#endif