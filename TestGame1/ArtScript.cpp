#include "ArtScript.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void ArtScript::onStart(void) {

}

void ArtScript::onUpdate(void) {
	Transform * transform = art->getComponent<Transform>();
	vec3 position = transform->getPosition();
	float playerX = position.x;
	float playerY = position.y;
	
	float dtime = getDeltaTime();

	float y = playerY + velY * dtime;
	if (y < boundaryHeight - transform->getScale().y / 2 && y > transform->getScale().y / 2) {
		transform->setPosition({ playerX, y, 0 });
		playerY = y;
	}
	else {
		velY = - velY;
	}

	
	float x = playerX + velX * dtime;
	if (x < boundaryWidth - transform->getScale().x / 2 && x > transform->getScale().x / 2) {
		transform->setPosition({ x, playerY, 0 });
		playerX = x;
	}
	else {
		velX = - velX;
	}
}