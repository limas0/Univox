#pragma once
#include "Renderer.h"
#include "Player.h"
#include "World\World.h"
#include "World\WorldRenderer.h"

class Game
{
public:
	static Game *game;
public:
	Game();
	~Game();

	void create();
	void destroy();

	void loop();
	void run();

	WE::Window &getWindow();//elpregnanto

	Renderer &getRenderer();
	Player &getPlayer();
	World &getWorld();
	WorldRenderer &getWorldRenderer();
private:
	Renderer renderer;
	WorldRenderer worldRenderer;

	Player player;
	World world;

	WE::Window window;
	WE::RenderStatistics renderStats;
};

