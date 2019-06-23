#pragma once
#include <Engine.h>

class GameControllerScript : public Script {
public:
	void onStart(void);
	void onUpdate(void);
	void * generate();
	int dispose();

	Object * player;
	Object * bulletPrefab;
	Object * hazardPrefab;
	Object * explosionPrefab;
	Object * camera;
	Object * uitext;

	void shoot(void);
	void hazard(void);

	int numberCrash;
	int numberHit;
	int numberShoot;
protected:
	float timeCounter;
	float hazardTime;
};