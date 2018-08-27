#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include "../Asset/Mesh.h"
#include "../Physics/CollisionListener.h"

class Collider : public Component {
public:
	Collider();
	void setCollidable(bool collidable);
	bool getCollidable();
	void addListener(CollisionListener * listener);
	CollisionListener ** getListener();
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

#endif