#include "Main.h"

#include <Engine.h>
#include "TestGames\Snek\SnekScene.h"

int main(int argc, char ** argv) {

	Engine * engine = Engine::getInstance();
	FrameGL * frame = FrameGL::getInstance();
	frame->init(argc, argv, "Try Sumtink", 800, 600);
	engine->setFrame(frame);
	engine->setScene(new SnekScene());
	engine->startGame();

	return 0;
}