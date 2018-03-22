#pragma once
#include "../../Header.h"

class Chunk;
class ChunkMesh;

struct AdjacentBlocks
{
	bool top = false;
	bool bottom = false;
	bool left = false;
	bool right = false;
	bool front = false;
	bool back = false;
};

using BlockFaces = AdjacentBlocks;

class ChunkMeshBuilder
{
public:
	ChunkMeshBuilder(Chunk *chunk, ChunkMesh *chunkMesh);
	~ChunkMeshBuilder();

	void build();

	inline bool isBlockCovered(int x, int y, int z) const;
	inline bool isBlockCovered(const AdjacentBlocks &adj) const;
	inline AdjacentBlocks getAdjacentBlocks(Vec3i &pos) const;

	inline void addBlock(int x, int y, int z, BlockFaces &faces);

private:
	Chunk *p_chunk = nullptr;
	ChunkMesh *p_mesh = nullptr;
	size_t verticesAdded = 0;
};