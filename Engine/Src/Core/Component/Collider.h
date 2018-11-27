#pragma once

#include "Component.h"
#include "../Asset/Mesh.h"
#include "../Physics/CollisionListener.h"

class DLLDIR Collider : public Component {
public:
	Collider();
	void setCollidable(bool collidable);
	bool getCollidable();
	void addListener(CollisionListener * listener);
	CollisionListener ** getListener();
	int getListenerCount();
	void setMesh(Mesh * mesh);
	Mesh * getMesh();

private:
	Mesh * mesh;
	bool collidable;
	CollisionListener ** listenerList;
	int listenerCount;
	int listenerSize;

	void checkSize();
};