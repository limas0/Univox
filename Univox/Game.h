#pragma once
#include "Renderer.h"
#include "Player.h"
#include "World/World.h"

class Game
{
public:
	static Game *game;
public:
	Game();
	~Game();

	void create();
	void destroy();

	void run();

	WE::Window &getWindow();//elpregnanto

	Renderer &getRenderer();
	Player &getPlayer();
private:
	Renderer renderer;
	Player player;
	World world;

	WE::Window window;
	WE::Message msg;
	WE::RenderStatistics renderStats;
};

