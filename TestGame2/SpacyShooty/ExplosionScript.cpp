#include "ExplosionScript.h"

void ExplosionScript::onStart() {
	printf("Explodon\n");
	startTime = getDeltaTime();
	object->getComponent<Sound>()->play();
}

void ExplosionScript::onUpdate() {
	if (getDeltaTime() > startTime + 5000);
		removeObject(object);
}

void * ExplosionScript::generate() {
	return new ExplosionScript();
}

int ExplosionScript::dispose() {
	return 0;
}