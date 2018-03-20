#include "ChunkMeshBuilder.h"
#include "Chunk.h"
#include "ChunkMesh.h"

ChunkMeshBuilder::ChunkMeshBuilder(Chunk *chunk, ChunkMesh *chunkMesh) :
	p_chunk(chunk),
	p_mesh(chunkMesh)
{

}

ChunkMeshBuilder::~ChunkMeshBuilder()
{

}

void ChunkMeshBuilder::build()
{
	WE::Timer timer;
	timer.start();

	for (int i = 0; i < Consts::CHUNK_SIZE; i++)
	{
		for (int j = 0; j < Consts::CHUNK_HEIGHT; j++)
		{
			for (int k = 0; k < Consts::CHUNK_SIZE; k++)
			{
				if (p_chunk->getBlock(i, j, k) == true)
				{
					if (!isBlockCovered(i, j, k))
					{
						//WE::PrimitiveBuilder::createCube(p_chunk->getVertices(), p_chunk->getIndices(), { float(i), float(j), float(k) }, { float(i) + 1.f, float(j) + 1.f, float(k) + 1.f });
						auto adjBlocks = getAdjacentBlocks(Vec3i(i, j, k));

						if(adjBlocks.left == false)
							p_mesh->addQuad({ float(i), float(j), float(k) }, { 1.f, 1.f }, { 1.f, 0.f, 0.f });
						if (adjBlocks.right == false)
							p_mesh->addQuad({ float(i) + 1.f, float(j), float(k) }, { 1.f, 1.f }, { -1.f, 0.f, 0.f });
						
						if (adjBlocks.bottom == false)
							p_mesh->addQuad({ float(i), float(j), float(k) }, { 1.f, 1.f }, { 0.f, -1.f, 0.f });
						if (adjBlocks.top == false)
							p_mesh->addQuad({ float(i), float(j) + 1.f, float(k) }, { 1.f, 1.f }, { 0.f, 1.f, 0.f });

						if (adjBlocks.back == false)
							p_mesh->addQuad({ float(i), float(j), float(k) }, { 1.f, 1.f }, { 0.f, 0.f, 1.f });
						if (adjBlocks.front == false)
							p_mesh->addQuad({ float(i), float(j), float(k) + 1.f }, { 1.f, 1.f }, { 0.f, 0.f, -1.f });
					}
				}
			}
		}
	}

	std::cout << "Chunk rebuilt in " << timer.stop() << "ms" << std::endl;
}

inline bool ChunkMeshBuilder::isBlockCovered(int x, int y, int z) const
{
	return p_chunk->getBlock(x + 1, y, z) && p_chunk->getBlock(x - 1, y, z) &&
		p_chunk->getBlock(x, y + 1, z) && p_chunk->getBlock(x, y - 1, z) &&
		p_chunk->getBlock(x, y, z + 1) && p_chunk->getBlock(x, y, z - 1);
}

inline AdjacentBlocks ChunkMeshBuilder::getAdjacentBlocks(Vec3i &pos) const
{
	AdjacentBlocks result;

	result.top = p_chunk->getBlock(pos.x, pos.y + 1, pos.z);
	result.bottom = p_chunk->getBlock(pos.x, pos.y - 1, pos.z);
	result.left = p_chunk->getBlock(pos.x - 1, pos.y, pos.z);
	result.right = p_chunk->getBlock(pos.x + 1, pos.y, pos.z);
	result.front = p_chunk->getBlock(pos.x, pos.y, pos.z + 1);
	result.back = p_chunk->getBlock(pos.x, pos.y, pos.z - 1);

	return result;
}
