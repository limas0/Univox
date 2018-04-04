#pragma once
#include "Renderer.h"
#include "Player.h"
#include "World\World.h"
#include "World\WorldRenderer.h"
#include "Mod\ModLoader.h"
#include "Mod\ModHandler.h"
#include "Registries\BlockRegistry.h"

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
	BlockRegistry &getBlockRegistry();
private:
	Renderer renderer;
	WorldRenderer worldRenderer;

	Player player;
	World world;

	BlockRegistry blockRegistry;

	ModLoader modLoader;
	ModHandler modHandler;

	WE::Window window;
	WE::RenderStatistics renderStats;
};

