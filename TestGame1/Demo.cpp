#include <Engine.h>
#include "SnekScene.h"
#include <stdio.h>

int main(int argc, char ** argv) {
	Engine * engine = Engine::getInstance();
	FrameGL * frame = FrameGL::getInstance();
	frame->init(argc, argv, "Try Sumtink", 800, 600);
	engine->setFrame(frame);
	engine->setScene(new SnekScene());
	engine->startGame();

	getchar();

	return 0;
}