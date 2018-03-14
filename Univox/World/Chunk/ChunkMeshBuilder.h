#pragma once
#include "../../Header.h"

class Chunk;

struct AdjacentBlocks
{
	bool top = false;
	bool bottom = false;
	bool left = false;
	bool right = false;
	bool front = false;
	bool back = false;
};

class ChunkMeshBuilder
{
public:
	ChunkMeshBuilder(Chunk *chunk);
	~ChunkMeshBuilder();

	void build();

	inline bool isBlockCovered(int x, int y, int z) const;
	inline AdjacentBlocks getAdjacentBlocks(Vec3i &pos) const;

private:
	Chunk *p_chunk = nullptr;
};