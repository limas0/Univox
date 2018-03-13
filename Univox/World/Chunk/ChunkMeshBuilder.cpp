#include "ChunkMeshBuilder.h"
#include "../Chunk.h"

ChunkMeshBuilder::ChunkMeshBuilder(Chunk *chunk) :
	p_chunk(chunk)
{

}

ChunkMeshBuilder::~ChunkMeshBuilder()
{

}

void ChunkMeshBuilder::build()
{
	for (int i = 0; i < Consts::CHUNK_SIZE; i++)
	{
		for (int j = 0; j < Consts::CHUNK_HEIGHT; j++)
		{
			for (int k = 0; k < Consts::CHUNK_SIZE; k++)
			{
				if (p_chunk->getBlock(i, j, k) == true)
				{
					if(!isBlockCovered(i, j, k))
						WE::PrimitiveBuilder::createCube(p_chunk->getVertices(), p_chunk->getIndices(), { float(i), float(j), float(k) }, { float(i) + 1.f, float(j) + 1.f, float(k) + 1.f });
				}
			}
		}
	}
}

inline bool ChunkMeshBuilder::isBlockCovered(int x, int y, int z) const
{
	return p_chunk->getBlock(x + 1, y, z) && p_chunk->getBlock(x - 1, y, z) &&
		p_chunk->getBlock(x, y + 1, z) && p_chunk->getBlock(x, y - 1, z) &&
		p_chunk->getBlock(x, y, z + 1) && p_chunk->getBlock(x, y, z - 1);
}