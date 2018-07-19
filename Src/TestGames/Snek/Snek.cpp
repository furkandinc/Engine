#ifndef SNEK_CPP
#define SNEK_CPP

#include "Snek.h"

float random(int a, int b) {
	return a + rand() % (b - a);
}

void Snek::onStart(void) {
	srand(time(NULL));

	this->puan = 0;

	setScreenSize(ekranGenislik, ekranYukseklik);

	hedef = createObject();
	hedef->getComponent<Mesh>()->setColor(255, 0, 0);
	hedef->getComponent<Transform>()->setPosition(600, 400);

	oyuncu = createObject();
	oyuncu->getComponent<Mesh>()->setColor(0, 255, 0);
	oyuncu->getComponent<Transform>()->setPosition(200, 400);
}

void Snek::onUpdate(void) {
	Transform * transform = oyuncu->getComponent<Transform>();
	float oyuncuX = transform->getX();
	float oyuncuY = transform->getY();
	float hiz = 25;
	float araZaman = getDeltaTime();

	if (keyStatus(Keys::KEY_UP_ARROW) == Keys::STATUS_PRESS) {
		float y = oyuncuY + hiz * araZaman;
		if (y<ekranGenislik) {
			transform->setPosition(oyuncuX, y);
		}
	}

	if (keyStatus(Keys::KEY_DOWN_ARROW) == Keys::STATUS_PRESS) {
		float y = oyuncuY - hiz * araZaman;
		if (y < ekranGenislik) {
			transform->setPosition(oyuncuX, y);
		}
	}

	if (keyStatus(Keys::KEY_LEFT_ARROW) == Keys::STATUS_PRESS) {
		float x = oyuncuX - hiz * araZaman;
		if (x > 0) {
			transform->setPosition(x, oyuncuY);
		}
	}

	if (keyStatus(Keys::KEY_RIGHT_ARROW) == Keys::STATUS_PRESS) {
		float x = oyuncuX + hiz * araZaman;
		if (x<ekranGenislik) {
			transform->setPosition(x, oyuncuY);
		}
	}

	if (isCollide(oyuncu, hedef)) {
		float yeniX = random(100, 700);
		float yeniY = random(100, 700);

		this->puan += 1;
		hedef->getComponent<Transform>()->setPosition(yeniX, yeniY);
		printf("%i \n" , puan);
	}
}

#endif