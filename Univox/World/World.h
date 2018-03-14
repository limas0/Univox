#pragma once
#include "Header.h"
#include "Chunk/Chunk.h"

namespace std {

template<>
struct hash<Vec2i>
{
	const int operator()(const Vec2i &index) const noexcept
	{
		std::hash<decltype(index.x)> hasher;
		const int valuex = int(hasher(index.x));
		const int valuey = int(hasher(index.y));
		return int(std::hash<decltype(index.x)>{}((valuex ^ valuey) >> 2));
	}
};

}

using ChunksMap = std::unordered_map<Vec2i, Chunk*>;

class World
{
public:
	World();
	~World();

	void create();
	void destroy();

	void update();

	std::tuple<bool, ChunksMap::const_iterator> chunkExists(Vec2i &index) const;

	Chunk *getChunk(Vec2i &index) const;
private:
	WE::Scene *scene = nullptr;

	ChunksMap chunks;
};

