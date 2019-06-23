#include <Engine.h>
#include <stdio.h>
#include "SpacyShooty\SpacyShootyScene.h"

int main(int argc, char ** argv) {
	Engine * engine = Engine::getInstance();
	FrameGL * frame = FrameGL::getInstance();
	frame->init(argc, argv, "Spacy Shooty", 1000, 600);
	engine->setFrame(frame);
	engine->setScene(new SpacyShootyScene());
	engine->startGame();

	getchar();

	return 0;
}