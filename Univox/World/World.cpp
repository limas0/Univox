#include "World.h"
#include "../Game.h"

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

	for (int i = 0; i < 1; i++)
	{
		for (int k = 0; k < 1; k++)
		{
			Chunk *chunk = new Chunk();
			chunk->create(Vec2i(i, k));
			//auto data = chunk->getChunkData().serialize();
			//chunk->getChunkData().deserialize(data);
			chunk->setMaterial("Default");
			chunk->setTranslation({ float(i * Consts::CHUNK_SIZE), 0.f, float(k * Consts::CHUNK_SIZE) });
			chunks.emplace(std::make_pair(Vec2i(i, k), chunk));
			scene->addObject(chunk);
		}
	}

	scene->setActiveCamera(GAME->getPlayer().getCamera());
}

void World::destroy()
{
}

void World::update()
{
	/*if (std::rand() % 10 == 5)
	{
		if (cubes.size() - 1 > 0)
		{
			int i = std::rand() % (cubes.size() - 1);
			scene->removeObject(cubes[i]);
			cubes.erase(cubes.begin() + i);
		}
	}*/
}

std::tuple<bool, ChunksMap::const_iterator> World::chunkExists(Vec2i &index) const
{
	ChunksMap::const_iterator result = chunks.find(index);
	return { result != chunks.end(), result };
}

Chunk *World::getChunk(Vec2i &index) const
{
	auto[exists, iter] = chunkExists(index);

	if (exists)
		return iter->second;

	return nullptr;
}
