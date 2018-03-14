#include "Header.h"
#include "Game.h"

int main()
{
	std::srand(unsigned int(time(NULL)));

	Game game;
	game.create();
	game.run();
	game.destroy();

	return 0;
}