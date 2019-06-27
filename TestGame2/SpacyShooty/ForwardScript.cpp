#include "ForwardScript.h"
#include "ExplosionScript.h"

void ForwardScript::onStart() {

}

void ForwardScript::onUpdate() {
	float dtime = getDeltaTime();

	if (object != nullptr) {
		Transform * transform = object->getComponent<Transform>();
		transform->setPosition(transform->getPosition() + this->movementSpeed * dtime);
		transform->setRotation(transform->getRotation() + this->angularSpeed * dtime);
		vec3 position = transform->globalPosition();
		if (position.x < minX || position.y < minY || position.x > maxX || position.y > maxY) {
			removeObject(object);
		}
	}
}

void * ForwardScript::generate() {
	ForwardScript * script = new ForwardScript();
	script->movementSpeed = movementSpeed;
	script->angularSpeed = angularSpeed;
	script->hazardPrefab = hazardPrefab;
	script->explosionPrefab = explosionPrefab;
	return script;
}

int ForwardScript::dispose() {
	return 0;
}

void ForwardScript::onCollide(Object * object) {
	if (strcmp(this->object->getTag(), "hazard") == 0) {
		if (strcmp(object->getTag(), "bullet") == 0) {
			if (this->object->getComponent<Transform>()->getScale().x > 99) {
				Transform * transform = this->object->getComponent<Transform>();
				Object * object1 = instantiate(hazardPrefab);
				Object * object2 = instantiate(hazardPrefab);

				object1->getComponent<Transform>()->setScale(vec3(50, 50, 50));
				object1->getComponent<ForwardScript>()->movementSpeed = vec3(-100, 20, 0);
				object1->getComponent<ForwardScript>()->angularSpeed = vec3(-60, -60, 0);
				object1->getComponent<ForwardScript>()->gameScript = gameScript;
				object1->getComponent<Transform>()->setPosition(transform->getPosition());
				object1->getComponent<Collider>()->setCollidable(true);
				object1->getComponent<Collider>()->addListener(object1->getComponent<ForwardScript>());

				object2->getComponent<Transform>()->setScale(vec3(50, 50, 50));
				object2->getComponent<ForwardScript>()->movementSpeed = vec3(-100, -20, 0);
				object2->getComponent<ForwardScript>()->angularSpeed = vec3(60, -60, 0);
				object2->getComponent<ForwardScript>()->gameScript = gameScript;
				object2->getComponent<Transform>()->setPosition(transform->getPosition());
				object2->getComponent<Collider>()->setCollidable(true);
				object2->getComponent<Collider>()->addListener(object2->getComponent<ForwardScript>());
				printf("Explosion %s\n", object2->getTag());
			}
			gameScript->numberHit++;
			
			removeObject(this->object);
			removeObject(object);
			Object * explosion = instantiate(explosionPrefab);
			explosion->getComponent<ExplosionScript>()->onStart();
		}
		else if (strcmp(object->getTag(), "ship") == 0) {
			gameScript->numberCrash++;
			removeObject(this->object);
			//removeObject(object);
			Object * explosion = instantiate(explosionPrefab);
			explosion->getComponent<ExplosionScript>()->onStart();
		}
	}
}