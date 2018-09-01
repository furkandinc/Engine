#include "SnekScript.h"
#include <Component\Collider.h>
#include <Asset\CubeMesh.h>

float random(int a, int b) {
	return a + rand() % (b - a);
}

void SnekScript::onStart(void) {
	srand(time(NULL));

	this->score = 0;

	setScreenSize(boundaryWidth, boundaryHeight);

	Collider * collider = player->getComponent<Collider>();
	collider->addListener(this);
}

void SnekScript::onUpdate(void) {
	Transform * transform = player->getComponent<Transform>();
	vec3 position = transform->getPosition();
	float playerX = position.x;
	float playerY = position.y;
	float speed = 400 ;
	float dtime = getDeltaTime();

	Transform * targetTransform = target->getComponent<Transform>();
	vec3 targetPosition = targetTransform->getPosition();
	float targetX = targetPosition.x;
	float targetY = targetPosition.y;

	if (keyStatus(Keys::KEY_UP) == Keys::STATUS_PRESS) {
		float y = playerY + speed * dtime;
		if (y < boundaryHeight - transform->getScale().y/2) {
			transform->setPosition({ playerX, y, 0});
			playerY = y;
		}
	}

	if (keyStatus(Keys::KEY_DOWN) == Keys::STATUS_PRESS) {
		float y = playerY - speed * dtime;
		if (y > transform->getScale().y / 2) {
			transform->setPosition({playerX, y, 0});
			playerY = y;
		}
	}

	if (keyStatus(Keys::KEY_LEFT) == Keys::STATUS_PRESS) {
		float x = playerX - speed * dtime;
		if (x > transform->getScale().x / 2) {
			transform->setPosition({ x, playerY, 0});
			playerX = x;
		}
	}

	if (keyStatus(Keys::KEY_RIGHT) == Keys::STATUS_PRESS) {
		float x = playerX + speed * dtime;
		if (x < boundaryWidth - transform->getScale().x/2) {
			transform->setPosition({ x, playerY, 0 });
			playerX = x;
		}
	}
	//printf("DeltaTime: %f, oX %f, oY %f, hX %f, hY %f \n", dtime, playerX, playerY, targetX, targetY);
}

void SnekScript::onCollide(Object * object) {
	if (object == target) {
		float newX = random(50, 750);
		float newY = random(50, 550);

		this->score += 1;
		target->getComponent<Transform>()->setPosition({ newX, newY, 0 });
		printf("SCORE: %i \n", score);
	}
}