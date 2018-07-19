#include "Main.h"

int main(int argc, char ** argv) {

	Engine * engine = Engine::getInstance();
	engine->setGame(new Snek());
	engine->startGame();

	return 0;
}