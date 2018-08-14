#include "Main.h"

int main(int argc, char ** argv) {

	Engine * engine = Engine::getInstance();
	FrameGL * frame = FrameGL::getInstance();
	frame->init(argc, argv, "Try Sumtink", 800, 600);
	engine->setFrame(frame);
	engine->setGame(new Snek());
	engine->startGame();

	return 0;
}