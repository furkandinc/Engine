#ifndef SNEK_CPP
#define SNEK_CPP

#include "Snek.h"

float random(int a, int b) {
	return a + rand() % (b - a);
}

void Snek::onStart(void) {
	srand(time(NULL));

	this->score = 0;

	setScreenSize(boundaryWidth, boundaryHeight);

	target = createObject();
	target->getComponent<Mesh>()->setColor(255, 0, 0);
	target->getComponent<Transform>()->setPosition(600, 300);
	target->getComponent<Transform>()->setScale(30, 30);

	player = createObject();
	player->getComponent<Mesh>()->setColor(0, 255, 0);
	player->getComponent<Transform>()->setPosition(200, 300);
	player->getComponent<Transform>()->setScale(100, 100);
}

void Snek::onUpdate(void) {
	Transform * transform = player->getComponent<Transform>();
	float playerX = transform->getX();
	float playerY = transform->getY();
	float speed = 100;
	float dtime = getDeltaTime();

	Transform * targetTransform = target->getComponent<Transform>();
	float targetX = targetTransform->getX();
	float targetY = targetTransform->getY();

	if (keyStatus(Keys::KEY_UP_ARROW) == Keys::STATUS_PRESS) {
		float y = playerY + speed * dtime;
		if (y < boundaryHeight - transform->getH()) {
			transform->setPosition(playerX, y);
			playerY = y;
		}
	}

	if (keyStatus(Keys::KEY_DOWN_ARROW) == Keys::STATUS_PRESS) {
		float y = playerY - speed * dtime;
		if (y > 0) {
			transform->setPosition(playerX, y);
			playerY = y;
		}
	}

	if (keyStatus(Keys::KEY_LEFT_ARROW) == Keys::STATUS_PRESS) {
		float x = playerX - speed * dtime;
		if (x > 0) {
			transform->setPosition(x, playerY);
			playerX = x;
		}
	}

	if (keyStatus(Keys::KEY_RIGHT_ARROW) == Keys::STATUS_PRESS) {
		float x = playerX + speed * dtime;
		if (x < boundaryWidth - transform->getW()) {
			transform->setPosition(x, playerY);
			playerX = x;
		}
	}

	if (isCollide(player, target)) {
		float newX = random(50, 750);
		float newY = random(50, 550);

		this->score += 1;
		target->getComponent<Transform>()->setPosition(newX, newY);
		printf("SCORE: %i \n" , score);
	}

	//	printf("DeltaTime: %f, oX %f, oY %f, hX %f, hY %f \n", dtime, playerX, playerY, targetX, targetY);
}

#endif