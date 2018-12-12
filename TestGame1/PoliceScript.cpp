#include "PoliceScript.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

float random(int a, int b) {
	return a + rand() % (b - a);
}

void PoliceScript::onStart(void) {
	srand(time(NULL));

	this->score = 0;

	setScreenSize(boundaryWidth, boundaryHeight);

	Collider * collider = police->getComponent<Collider>();
	collider->addListener(this);
}

void PoliceScript::onUpdate(void) {
	Transform * transform = police->getComponent<Transform>();
	vec3 position = transform->getPosition();
	float policeX = position.x;
	float policeY = position.y;
	float speed = 600;
	float dtime = getDeltaTime();

	Transform * thiefTransform = thief->getComponent<Transform>();
	vec3 thiefPosition = thiefTransform->getPosition();
	float thiefX = thiefPosition.x;
	float thiefY = thiefPosition.y;

	if (keyStatus(Keys::KEY_UP) == Keys::STATUS_PRESS) {
		float y = policeY + speed * dtime;
		if (y < boundaryHeight - transform->getScale().y / 2) {
			transform->setPosition({ policeX, y, 0 });
			policeY = y;
		}
	}

	if (keyStatus(Keys::KEY_DOWN) == Keys::STATUS_PRESS) {
		float y = policeY - speed * dtime;
		if (y > transform->getScale().y / 2) {
			transform->setPosition({ policeX, y, 0 });
			policeY = y;
		}
	}

	if (keyStatus(Keys::KEY_LEFT) == Keys::STATUS_PRESS) {
		float x = policeX - speed * dtime;
		if (x > transform->getScale().x / 2) {
			transform->setPosition({ x, policeY, 0 });
			policeX = x;
		}
	}

	if (keyStatus(Keys::KEY_RIGHT) == Keys::STATUS_PRESS) {
		float x = policeX + speed * dtime;
		if (x < boundaryWidth - transform->getScale().x / 2) {
			transform->setPosition({ x, policeY, 0 });
			policeX = x;
		}
	}
	//printf("DeltaTime: %f, oX %f, oY %f, hX %f, hY %f \n", dtime, policeX, policeY, thiefX, thiefY);
}

void PoliceScript::onCollide(Object * object) {
	if (object == thief) {
		float newX = random(50, boundaryWidth - 50);
		float newY = random(50, boundaryHeight - 50);

		this->score += 1;
		thief->getComponent<Transform>()->setPosition({ newX, newY, 0 });
		printf("SCORE: %i \n", score);
	}
	if (object == art) {
		float newX = random(50, boundaryWidth - 50);
		float newY = random(50, boundaryHeight - 50);

		this->score -= 1;
		art->getComponent<Transform>()->setPosition({ newX, newY, 0 });
		printf("SCORE: %i \n", score);
	}

	Sound * sound = police->getComponent<Sound>();
	sound->play();
}

void * PoliceScript::generate() {
	PoliceScript * ts = new PoliceScript();
	ts->art = art;
	ts->thief = thief;
	ts->police = police;
	return ts;
}

int PoliceScript::dispose() {
	return 0;
}