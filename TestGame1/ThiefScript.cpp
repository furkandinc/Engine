#include "ThiefScript.h"
#include <includes\Angel.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

float random1(int a, int b) {
	return a + rand() % (b - a);
}

void ThiefScript::onStart(void) {
	srand(time(NULL));

	this->score = 0;

	setScreenSize(boundaryWidth, boundaryHeight);

	Collider * collider = thief->getComponent<Collider>();
	collider->addListener(this);
}

void ThiefScript::onUpdate(void) {
	Transform * transform = thief->getComponent<Transform>();
	vec3 position = transform->getPosition();
	float playerX = position.x;
	float playerY = position.y;
	float speed = 1200;
	float dtime = getDeltaTime();

	if (keyStatus(Keys::KEY_W) == Keys::STATUS_PRESS) {
		float y = playerY + speed * dtime;
		if (y < boundaryHeight - transform->getScale().y / 2) {
			transform->setPosition({ playerX, y, 0 });
			playerY = y;
		}
	}

	if (keyStatus(Keys::KEY_S) == Keys::STATUS_PRESS) {
		float y = playerY - speed * dtime;
		if (y > transform->getScale().y / 2) {
			transform->setPosition({ playerX, y, 0 });
			playerY = y;
		}
	}

	if (keyStatus(Keys::KEY_A) == Keys::STATUS_PRESS) {
		float x = playerX - speed * dtime;
		if (x > transform->getScale().x / 2) {
			transform->setPosition({ x, playerY, 0 });
			playerX = x;
		}
	}

	if (keyStatus(Keys::KEY_D) == Keys::STATUS_PRESS) {
		float x = playerX + speed * dtime;
		if (x < boundaryWidth - transform->getScale().x / 2) {
			transform->setPosition({ x, playerY, 0 });
			playerX = x;
		}
	}
	//printf("DeltaTime: %f, oX %f, oY %f, hX %f, hY %f \n", dtime, playerX, playerY, thiefX, thiefY);
}

void ThiefScript::onCollide(Object * object) {
	if (object == art) {
		float newX = random1(50, boundaryWidth - 50);
		float newY = random1(50, boundaryHeight - 50);

		this->score += 1;
		art->getComponent<Transform>()->setPosition({ newX, newY, 0 });
		printf("Thief: %i \n", score);
	}
}