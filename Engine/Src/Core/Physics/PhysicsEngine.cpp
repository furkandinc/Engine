#ifndef PHYSICS_ENGINE_CPP
#define PHYSICS_ENGINE_CPP

#include "PhysicsEngine.h"
#include "CollisionPhysics.h"

PhysicsEngine::PhysicsEngine() {
	objectHandler = nullptr;
}

void PhysicsEngine::tick() {
	if (objectHandler == nullptr)
		return;

	Object ** list = objectHandler->getList();
	Object ** collidable = (Object **)malloc(sizeof(Object *) * objectHandler->getSize());
	int collidableSize = 0;
	for (int i = 0; i < objectHandler->getSize(); i++) {
		Object * object = list[i];
		Collider * collider = object->getComponent<Collider>();
		if (collider != nullptr) {
			if (collider->getCollidable() && collider->getMesh()!=nullptr) {
				Transform * transform = object->getComponent<Transform>();
				if (transform != nullptr) {
					collidable[collidableSize++] = object;
				}
			}
		}
	}

	for (int i = 0; i < collidableSize - 1; i++) {
		Object * object1 = collidable[i];
		Collider * collider1 = object1->getComponent<Collider>();
		Transform * transform1 = object1->getComponent<Transform>();

		for (int j = i + 1; j < collidableSize; j++) {
			Object * object2 = collidable[j];
			Collider * collider2 = object2->getComponent<Collider>();
			Transform * transform2 = object2->getComponent<Transform>();

			bool result = isCollide(collider1->getMesh(), transform1, collider2->getMesh(), transform2);
			if (result) {
				CollisionListener ** listeners1 = collider1->getListener();
				for (int l = 0; l < collider1->getListenerCount(); l++) {
					listeners1[l]->onCollide(object2);
				}
				CollisionListener ** listeners2 = collider2->getListener();
				for (int l = 0; l < collider2->getListenerCount(); l++) {
					listeners2[l]->onCollide(object1);
				}
			}
		}
	}
}

void PhysicsEngine::setObjectHandler(ObjectHandler * objectHandler) {
	this->objectHandler = objectHandler;
}

#endif