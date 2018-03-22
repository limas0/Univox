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

	p_mesh->getVertices().reserve(Consts::CHUNK_VOLUME * 6 * 6 / 2);

	for (int i = 0; i < Consts::CHUNK_SIZE; i++)
	{
		for (int j = 0; j < Consts::CHUNK_HEIGHT; j++)
		{
			for (int k = 0; k < Consts::CHUNK_SIZE; k++)
			{
				if (p_chunk->getBlock(i, j, k) == true)
				{
					auto adjBlocks = getAdjacentBlocks(Vec3i(i, j, k));

					if (!isBlockCovered(adjBlocks))
					{
						addBlock(i, j, k, adjBlocks);
					}
				}
			}
		}
	}

	p_mesh->getVertices().resize(verticesAdded);

	std::cout << "Chunk rebuilt in " << timer.stop() << "ms" << std::endl;
}

inline bool ChunkMeshBuilder::isBlockCovered(int x, int y, int z) const
{
	return p_chunk->getBlock(x + 1, y, z) && p_chunk->getBlock(x - 1, y, z) &&
		p_chunk->getBlock(x, y + 1, z) && p_chunk->getBlock(x, y - 1, z) &&
		p_chunk->getBlock(x, y, z + 1) && p_chunk->getBlock(x, y, z - 1);
}

inline bool ChunkMeshBuilder::isBlockCovered(const AdjacentBlocks &adj) const
{
	return adj.back && adj.bottom && adj.front && adj.left && adj.right && adj.top;
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

inline void ChunkMeshBuilder::addBlock(int x, int y, int z, BlockFaces &faces)
{
	if (faces.left == false)
	{
		p_mesh->addQuad({ float(x), float(y), float(z) }, { 1.f, 1.f }, { -1.f, 0.f, 0.f });
		verticesAdded += 6;
	}

	if (faces.right == false)
	{
		p_mesh->addQuad({ float(x) + 1.f, float(y), float(z) }, { 1.f, 1.f }, { 1.f, 0.f, 0.f });
		verticesAdded += 6;
	}


	if (faces.bottom == false)
	{
		p_mesh->addQuad({ float(x), float(y), float(z) }, { 1.f, 1.f }, { 0.f, -1.f, 0.f });
		verticesAdded += 6;
	}
		
	if (faces.top == false)
	{
		p_mesh->addQuad({ float(x), float(y) + 1.f, float(z) }, { 1.f, 1.f }, { 0.f, 1.f, 0.f });
		verticesAdded += 6;
	}
		

	if (faces.back == false)
	{
		p_mesh->addQuad({ float(x), float(y), float(z) }, { 1.f, 1.f }, { 0.f, 0.f, -1.f });
		verticesAdded += 6;
	}
		
	if (faces.front == false)
	{
		p_mesh->addQuad({ float(x), float(y), float(z) + 1.f }, { 1.f, 1.f }, { 0.f, 0.f, 1.f });
		verticesAdded += 6;
	}
}
