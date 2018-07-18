#include "Core\Engine.h"
#include "TestGames\Snek\Snek.h"

int main(int argc, char ** argv) {

	Engine * engine = Engine::getInstance();
	engine->setGame((Script *)new Snek());
	engine->startGame();

	return 0;
}