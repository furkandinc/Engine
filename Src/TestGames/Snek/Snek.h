#ifndef SNEK_H
#define SNEK_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "..\..\Core\Engine.h"
#include "..\..\Core\Component\Transform.h"
#include "..\..\Core\Component\Mesh.h"
#include "..\..\Core\Input\Keys.h"
#include "..\..\Core\Logic\Script.h"

float random(int a, int b) {
	return a + rand() % (b - a);
}

class Snek: public Script {
public:
	virtual void onStart();
	virtual void onUpdate();
private:
	Object * oyuncu;
	Object * hedef;

	int puan;
	int ekranGenislik = 800;
	int ekranYukseklik = 800;
};
#endif