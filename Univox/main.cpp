#include "Header.h"
#include "Game.h"

int main()
{
	Game game;
	game.create();
	game.run();
	game.destroy();

	return 0;
}