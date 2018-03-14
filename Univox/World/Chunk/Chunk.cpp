#include "Chunk.h"
#include "ChunkMeshBuilder.h"

Chunk::Chunk() :
	Mesh()
{
}

Chunk::~Chunk()
{

}

void Chunk::create()
{
	create(Vec2i(0, 0));
}

void Chunk::create(Vec2i &index)
{
	m_index = index;

	for (int i = 0; i < Consts::CHUNK_SIZE; i++)
	{
		for (int j = 0; j < Consts::CHUNK_HEIGHT; j++)
		{
			for (int k = 0; k < Consts::CHUNK_SIZE; k++)
			{
				if ((i / 4 % 2 == 0) && (j / 2 % 2 == 0) && (k / 1 % 2 == 0))
					m_data.blocks[translateIndex(i, j, k)] = true;
				else
					m_data.blocks[translateIndex(i, j, k)] = false;
			}
		}
	}



	ChunkMeshBuilder(this).build();

	boundingBox.create({ 0.f, 0.f, 0.f }, { float(Consts::CHUNK_SIZE), float(Consts::CHUNK_HEIGHT), float(Consts::CHUNK_SIZE) });

	Mesh::create();
}

void Chunk::destroy()
{
	Mesh::destroy();
}

void Chunk::update()
{
	Mesh::update();
}

void Chunk::draw()
{
	Mesh::draw();
}
