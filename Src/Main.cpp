#include "Core\Engine.cpp"
#include "TestGames\Snek\Snek.cpp"

int main() {
	Engine * engine = Engine::getInstance();
	engine->setGame((Script *)new Snek());
	engine->startGame();
}