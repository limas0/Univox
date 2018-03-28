#include "ChunkMesh.h"

ChunkMesh::ChunkMesh()
{
}

ChunkMesh::~ChunkMesh()
{
}

void ChunkMesh::create(Vec2i index)
{
	m_index = index;
	boundingBox.create({ 0.f, 0.f, 0.f }, { float(Consts::CHUNK_SIZE), float(Consts::CHUNK_HEIGHT), float(Consts::CHUNK_SIZE) });
	Mesh::create();
}

void ChunkMesh::destroy()
{
	Mesh::destroy();
	//std::cout << "Destroyed chunk mesh" << std::endl;
}

void ChunkMesh::update()
{
	Mesh::update();
}

void ChunkMesh::draw()
{
	Mesh::draw();
}
