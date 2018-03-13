#pragma once
#include "../../Header.h"

class Chunk;

class ChunkMeshBuilder
{
public:
	ChunkMeshBuilder(Chunk *chunk);
	~ChunkMeshBuilder();

	void build();

	inline bool isBlockCovered(int x, int y, int z) const;

private:
	Chunk *p_chunk = nullptr;
};