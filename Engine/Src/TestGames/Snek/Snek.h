#ifndef SNEK_H
#define SNEK_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "..\..\Core\Object\Object.h"
#include "..\..\Core\Engine.h"
#include "..\..\Core\Component\Transform.h"
#include "..\..\Core\Component\Renderer.h"
#include "..\..\Core\Input\Keys.h"
#include "..\..\Core\Asset\Script.h"
#include "..\..\Core\Physics\CollisionListener.h"

float random(int a, int b);
class Snek: public Script, public CollisionListener {
public:
	void onStart(void);
	void onUpdate(void);
	void onCollide(Object * object);
private:
	Object * player;
	Object * target;

	int score;
	int boundaryWidth = 800;
	int boundaryHeight = 600;
};
#endif