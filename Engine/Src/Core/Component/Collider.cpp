#include "Collider.h"
#include <stdlib.h>

Collider::Collider() {
	mesh = nullptr;
	collidable = false;
	listenerCount = 0;
	listenerSize = 10;
	listenerList = (CollisionListener **)malloc(sizeof(CollisionListener *) * listenerSize);
}

void Collider::setCollidable(bool collidable) {
	this->collidable = collidable;
}

bool Collider::getCollidable() {
	return collidable;
}

void Collider::addListener(CollisionListener * listener) {
	checkSize();
	listenerList[listenerCount++] = listener;
}

CollisionListener ** Collider::getListener() {
	return listenerList;
}

int Collider::getListenerCount() {
	return listenerCount;
}

void Collider::setMesh(Mesh * mesh) {
	this->mesh = mesh;
}

Mesh * Collider::getMesh() {
	return this->mesh;
}

void Collider::checkSize() {
	if (listenerCount == listenerSize) {
		listenerSize *= 2;
		CollisionListener ** tempList = (CollisionListener **)malloc(sizeof(CollisionListener) * listenerSize);
		for (int i = 0; i < listenerCount; i++) {
			tempList[i] = listenerList[i];
		}
		free(listenerList);
		listenerList = tempList;
	}
}

void * Collider::generate() {
	Collider * c = new Collider();
	c->setMesh((Mesh *)mesh->generate());
	c->collidable = collidable;
	return c;
}

int Collider::dispose() {
	if (mesh != nullptr)
		mesh->dispose();
	free(mesh);
	free(listenerList);
	return 0;
}