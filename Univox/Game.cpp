#include "Game.h"
Game *Game::game;

Game::Game()
{
	Game::game = this;
}

Game::~Game()
{
}

void Game::create()
{
	window.create("Univox", 1280, 720);
	renderer.create();
	player.create();

	world.create();
}

void Game::destroy()
{
	world.destroy();
	player.destroy();
	renderer.destroy();
	window.destroy();
}

void Game::run()
{
	while (window.isOpen())
	{
		while (window.peekMessage(msg))
		{
			if (msg.is(WM_QUIT))
				window.close();
		}

		renderer.clear();
		renderer.update();
		player.update();

		renderStats.update();
		renderStats.draw();

		renderer.render();
	}
}

WE::Window &Game::getWindow()
{
	return window;
}

Renderer &Game::getRenderer()
{
	return renderer;
}

Player &Game::getPlayer()
{
	return player;
}
