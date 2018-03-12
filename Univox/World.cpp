#include "World.h"
#include "Game.h"

World::World()
{
}

World::~World()
{
}

void World::create()
{
	auto &sceneHandler = GAME->getRenderer().getEngine().getSceneHandler();
	scene = sceneHandler.addScene("World");
	sceneHandler.setActiveScene(scene);

	for (float i = 0; i < 16; i++)
	{
		for (float j = 0; j < 16; j++)
		{
			for (float k = 0; k < 16; k++)
			{
				WE::Cube *cube = new WE::Cube();
				cube->create();
				cube->setMaterial("Default");
				cube->setTranslation({i, j, k});

				scene->addObject(cube);
			}
		}
	}

	scene->setActiveCamera(GAME->getPlayer().getCamera());
}

void World::destroy()
{
}
