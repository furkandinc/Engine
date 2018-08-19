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
	target->getComponent<Transform>()->setPosition(600, 400);

	player = createObject();
	player->getComponent<Mesh>()->setColor(0, 255, 0);
	player->getComponent<Transform>()->setPosition(200, 400);
}

void Snek::onUpdate(void) {
	Transform * transform = player->getComponent<Transform>();
	float playerX = transform->getX();
	float playerY = transform->getY();
	float hiz = 25;
	float araZaman = getDeltaTime();

	Transform * targetTransform = target->getComponent<Transform>();
	float targetX = targetTransform->getX();
	float targetY = targetTransform->getY();

	if (keyStatus(Keys::KEY_UP_ARROW) == Keys::STATUS_PRESS) {
		float y = playerY + hiz * araZaman;
		if (y<boundaryWidth) {
			transform->setPosition(playerX, y);
		}
	}

	if (keyStatus(Keys::KEY_DOWN_ARROW) == Keys::STATUS_PRESS) {
		float y = playerY - hiz * araZaman;
		if (y < boundaryWidth) {
			transform->setPosition(playerX, y);
		}
	}

	if (keyStatus(Keys::KEY_LEFT_ARROW) == Keys::STATUS_PRESS) {
		float x = playerX - hiz * araZaman;
		if (x > 0) {
			transform->setPosition(x, playerY);
		}
	}

	if (keyStatus(Keys::KEY_RIGHT_ARROW) == Keys::STATUS_PRESS) {
		float x = playerX + hiz * araZaman;
		if (x<boundaryWidth) {
			transform->setPosition(x, playerY);
		}
	}

	if (isCollide(player, target)) {
		float newX = random(100, 700);
		float newY = random(100, 500);

		this->score += 1;
		target->getComponent<Transform>()->setPosition(newX, newY);
		printf("SCORE: %i \n" , score);
	}

	//	printf("DeltaTime: %f, oX %f, oY %f, hX %f, hY %f \n", araZaman, playerX, playerY, targetX, targetY);
}

#endif