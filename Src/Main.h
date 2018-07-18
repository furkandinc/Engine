#include "Core\Engine.h"
#include "TestGames\Snek\Snek.h"

int main() {
	Engine * engine = Engine::getInstance();
	engine->setGame((Script *)new Snek());
	engine->startGame();
}