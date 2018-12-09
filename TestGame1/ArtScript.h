#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <Engine.h>

class ArtScript : public Script {
public:
	void onStart(void);
	void onUpdate(void);

	Object * art;

	int boundaryWidth;
	int boundaryHeight;
private:
	int velX = 150, velY = 150;
};