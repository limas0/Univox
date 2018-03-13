#pragma once
#include "../Header.h"

class Chunk : public WE::Mesh
{
public:
	Chunk();
	~Chunk();

	void create();
	void create(Vec2i &index);
	void destroy();

	void update();
	void draw();

	inline bool getBlock(int x, int y, int z) const;

private:
	Vec2i m_index = { 0, 0 };

	bool blocks[Consts::CHUNK_SIZE][Consts::CHUNK_HEIGHT][Consts::CHUNK_SIZE];
};

inline bool Chunk::getBlock(int x, int y, int z) const
{
	if(x < Consts::CHUNK_SIZE && x >= 0 &&
		y < Consts::CHUNK_HEIGHT && y >= 0 &&
		z < Consts::CHUNK_SIZE && z >= 0)
		return blocks[x][y][z];

	return false;
}

