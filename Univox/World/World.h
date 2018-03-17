#pragma once
#include "Header.h"
#include "Chunk/Chunk.h"

class World
{
public:
	using ChunkMap = std::unordered_map<Vec2i, Chunk*>;

	World();
	~World();

	void create();
	void destroy();

	void update();

	void setChunk(Vec2i &index, Chunk *chunk);
	inline Chunk *getChunk(Vec2i &index);

	//[bool exists, iter]
	inline std::tuple<bool, ChunkMap::const_iterator> getChunkIter(Vec2i &index);
private:
	ChunkMap chunks;
};

inline Chunk *World::getChunk(Vec2i &index)
{
	ChunkMap::iterator result = chunks.find(index);
	return result != chunks.end() ? result->second : nullptr;
}

