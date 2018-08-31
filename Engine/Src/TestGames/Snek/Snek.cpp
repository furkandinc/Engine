#ifndef SNEK_CPP
#define SNEK_CPP

#include "Snek.h"
#include "../../Core/includes/Reader.h"

float random(int a, int b) {
	return a + rand() % (b - a);
}

void Snek::onStart(void) {
	srand(time(NULL));

	this->score = 0;

	setScreenSize(boundaryWidth, boundaryHeight);

	target = createObject();
	target->getComponent<Renderer>()->getMaterial()->setDiffuseColor({ 1, 0, 0, 1 });
	target->getComponent<Transform>()->setPosition({ 600, 300, 0});
	target->getComponent<Transform>()->setScale({30, 30, 30});

	Collider * tCol = new Collider();
	tCol->setMesh(new CubeMesh());
	tCol->setCollidable(true);
	target->addComponent(tCol);
	
	player = createObject();
	player->getComponent<Renderer>()->getMaterial()->setDiffuseColor({ 0, 1, 0, 1 });
	player->getComponent<Transform>()->setPosition({ 200, 300 , 0});
	player->getComponent<Transform>()->setScale({ 100, 100, 100 });
	
	Collider * pCol = new Collider();
	pCol->setMesh(new CubeMesh());
	pCol->setCollidable(true);
	player->addComponent(pCol);

	pCol->addListener(this);
}

void Snek::onUpdate(void) {
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
	//	printf("DeltaTime: %f, oX %f, oY %f, hX %f, hY %f \n", dtime, playerX, playerY, targetX, targetY);
}

void Snek::onCollide(Object * object) {
	if (object == target) {
		float newX = random(50, 750);
		float newY = random(50, 550);

		this->score += 1;
		target->getComponent<Transform>()->setPosition({ newX, newY, 0 });
		printf("SCORE: %i \n", score);
	}
}
#endif