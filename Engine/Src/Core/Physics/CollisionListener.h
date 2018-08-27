#ifndef COLLISION_LISTENER_H
#define COLLISION_LISTENER_H

class Object;

class CollisionListener {
public:
	virtual void onCollide(Object * object) = 0;
};

#endif