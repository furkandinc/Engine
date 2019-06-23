#include "PlayerControllerScript.h"

void PlayerControllerScript::onStart(void) {

}

void PlayerControllerScript::onUpdate(void) {

	float dtime = getDeltaTime();

	if (keyStatus(Keys::KEY_LEFT) == Keys::STATUS_PRESS) {
		currentSpeedX -= maxSpeed * dtime * 4;
		if (currentSpeedX < -maxSpeed) {
			currentSpeedX = -maxSpeed;
		}
	}
	else if (keyStatus(Keys::KEY_RIGHT) == Keys::STATUS_PRESS) {
		currentSpeedX += maxSpeed * dtime * 4;
		if (currentSpeedX > maxSpeed) {
			currentSpeedX = maxSpeed;
		}
	}
	else {
		if (currentSpeedX > maxSpeed / 10) {
			currentSpeedX -= maxSpeed * dtime * 2;
		}
		else if (currentSpeedX < -maxSpeed / 10) {
			currentSpeedX += maxSpeed * dtime * 2;
		}
		else {
			currentSpeedX = 0;
		}
	}

	if (keyStatus(Keys::KEY_UP) == Keys::STATUS_PRESS){
		currentSpeedY += maxSpeed * dtime * 4;
		if (currentSpeedY > maxSpeed) {
			currentSpeedY = maxSpeed;
		}
	}
	else if (keyStatus(Keys::KEY_DOWN) == Keys::STATUS_PRESS) {
		currentSpeedY -= maxSpeed * dtime * 4;
		if (currentSpeedY < -maxSpeed) {
			currentSpeedY = -maxSpeed;
		}
	}
	else {
		if (currentSpeedY > maxSpeed / 10) {
			currentSpeedY -= maxSpeed * dtime * 2;
		}
		else if (currentSpeedY < -maxSpeed / 10) {
			currentSpeedY += maxSpeed * dtime * 2;
		}
		else {
			currentSpeedY = 0;
		}
	}

	Transform * transform = player->getComponent<Transform>();
	vec3 position = transform->getPosition();
	float playerX = position.x;
	float playerY = position.y;
	float playerZ = position.z;
	
	vec3 rotation = transform->getRotation();
	
	float roll = (currentSpeedY * 30.0) / maxSpeed;
	transform->setRotation({ -roll , rotation.y, rotation.z });

	float scaleHalf = transform->getScale().y / 2;
	if (playerY + dtime * currentSpeedY > boundaryHeight - scaleHalf
		|| playerY + dtime * currentSpeedY < 0 + scaleHalf) {
		playerY = playerY;
	}
	else {
		playerY = playerY + dtime * currentSpeedY;
	}

	if (playerX + dtime * currentSpeedX > boundaryWidth - scaleHalf
		|| playerX + dtime * currentSpeedX < 0 + scaleHalf) {
		playerX = playerX;
	} else {
		playerX = playerX + dtime * currentSpeedX;
	}

	transform->setPosition({ playerX, playerY, playerZ });
}

void * PlayerControllerScript::generate() {
	PlayerControllerScript * p = new PlayerControllerScript();
	p->player = player;
	return p;
}

int PlayerControllerScript::dispose() {
	return 0;
}