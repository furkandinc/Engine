#include "GameControllerScript.h"
#include "ForwardScript.h"
#include "ExplosionScript.h"

float random2(int a, int b) {
	return a + rand() % (b - a);
}

void GameControllerScript::onStart() {
	srand(time(NULL));

	setScreenSize(1280, 720);

	hazardTime = 1;
	timeCounter = 0;
	numberCrash = 0;
	numberShoot = 0;
	numberHit = 0;
	hazard();
}

void GameControllerScript::onUpdate() {
	timeCounter += getDeltaTime();

	if (keyStatus(Keys::KEY_SPACE) == Keys::STATUS_PRESSED) {
		shoot();	
	}

	Transform * transform = camera->getComponent<Transform>();
	
	if (keyStatus(Keys::KEY_A) == Keys::STATUS_PRESS) {
		transform->setRotation(transform->getRotation() + vec3(0, 0, 1));
	}
	if (keyStatus(Keys::KEY_D) == Keys::STATUS_PRESS) {
		transform->setRotation(transform->getRotation() + vec3(0, 0, -1));
	}
	if (keyStatus(Keys::KEY_W) == Keys::STATUS_PRESS) {
		transform->setRotation(transform->getRotation() + vec3(0, 1, 0));
	}
	if (keyStatus(Keys::KEY_S) == Keys::STATUS_PRESS) {
		transform->setRotation(transform->getRotation() + vec3(0, -1, 0));
	}
	if (keyStatus(Keys::KEY_Q) == Keys::STATUS_PRESS) {
		transform->setRotation(transform->getRotation() + vec3(1, 0, 0));
	}
	if (keyStatus(Keys::KEY_E) == Keys::STATUS_PRESS) {
		transform->setRotation(transform->getRotation() + vec3(-1, 0, 0));
	}
	PerspectiveCamera * pCam = (PerspectiveCamera*)camera;
	if (keyStatus(Keys::KEY_Z) == Keys::STATUS_PRESS) {
		pCam->setFov(pCam->getFov() + 0.1);
	}
	if (keyStatus(Keys::KEY_X) == Keys::STATUS_PRESS) {
		pCam->setFov(pCam->getFov() - 0.1);
	}



	if (timeCounter > hazardTime) {
		hazard();
		hazardTime += 1;
	}

	char * text = (char*)malloc(sizeof(char) * 100);
	char buf[10];
	strcpy(text, "Crash: ");
	itoa(numberCrash, buf, 10);
	strcat(text, buf);
	strcat(text, "\nHit: ");
	itoa(numberHit, buf, 10);
	strcat(text, buf);
	strcat(text, "\nShoot: ");
	itoa(numberShoot, buf, 10);
	strcat(text, buf);
	uitext->getComponent<UIText>()->setText(text);
}

void GameControllerScript::hazard() {
	Object * objHazard = instantiate(hazardPrefab);
	objHazard->getComponent<Transform>()->setPosition(vec3(1200, random2(100, 500), 500));
	objHazard->getComponent<Transform>()->setScale(vec3(100, 100, 100));
	ForwardScript * script = objHazard->getComponent<ForwardScript>();
	script->gameScript = this;
	objHazard->getComponent<Collider>()->addListener(script);
	script->angularSpeed = vec3(60, 60, 0);
	script->movementSpeed = vec3(-100, 0, 0);
}

void GameControllerScript::shoot() {
	if (player != nullptr) {
		Transform * pTransform = player->getComponent<Transform>();
		Object * bullet = instantiate(bulletPrefab);

		ForwardScript * forwardScript = bullet->getComponent<ForwardScript>();
		forwardScript->movementSpeed = vec3(1000, 0, 0);
		forwardScript->gameScript = this;

		bullet->getComponent<Transform>()->setPosition(pTransform->getPosition());
		bullet->getComponent<Sound>()->play();
		numberShoot++;
	}
}

void * GameControllerScript::generate() {
	GameControllerScript * g = new GameControllerScript();
	g->bulletPrefab = bulletPrefab;
	g->explosionPrefab = explosionPrefab;
	return g;
}

int GameControllerScript::dispose() {
	return 0;
}