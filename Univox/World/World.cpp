#include "World.h"

World::World()
{
}

World::~World()
{
}

void World::create()
{

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

void World::setChunk(Vec2i &index, Chunk *chunk)
{
	if (auto[exists, iter] = getChunkIter(index); exists)
	{
		iter->second->destroy();
		delete iter->second;
		chunks.erase(iter);
	}

	chunks[index] = chunk;
}

inline std::tuple<bool, World::ChunkMap::const_iterator> World::getChunkIter(Vec2i &index)
{
	ChunkMap::iterator result = chunks.find(index);
	return { result != chunks.end(), result };
}
