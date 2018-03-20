#pragma once
#include "ChunkData.h"

class Chunk
{
public:
	static inline const int translateIndex(Vec3i &index);
	static inline const int translateIndex(int x, int y, int z);
	static inline const Vec3i translateIndex(int index);
public:
	Chunk();
	~Chunk();

	void create();
	void create(Vec2i &index);
	void destroy();

	inline bool getBlock(int x, int y, int z) const;

	inline void setChunkData(ChunkData &data);
	inline ChunkData &getChunkData();

private:
	Vec2i m_index = { 0, 0 };

	ChunkData m_data;
};

inline bool Chunk::getBlock(int x, int y, int z) const
{
	if(x < Consts::CHUNK_SIZE && x >= 0 &&
		y < Consts::CHUNK_HEIGHT && y >= 0 &&
		z < Consts::CHUNK_SIZE && z >= 0)
		return m_data.blocks[translateIndex(x, y, z)];

	return false;
}

inline void Chunk::setChunkData(ChunkData &data)
{
	m_data = data;
}

inline ChunkData &Chunk::getChunkData()
{
	return m_data;
}

inline const int Chunk::translateIndex(Vec3i &index)
{
	return index.x + index.y * Consts::CHUNK_SIZE + index.z * Consts::CHUNK_WALL_AREA;
}

inline const int Chunk::translateIndex(int x, int y, int z)
{
	return x + y * Consts::CHUNK_SIZE + z * Consts::CHUNK_WALL_AREA;
}

inline const Vec3i Chunk::translateIndex(int index)
{
	const int x = index % Consts::CHUNK_SIZE;
	const int y = (index / Consts::CHUNK_SIZE) % Consts::CHUNK_HEIGHT;
	return Vec3i(x, y, index / Consts::CHUNK_WALL_AREA);
}

