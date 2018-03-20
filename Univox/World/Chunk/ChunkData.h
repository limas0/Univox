#pragma once
#include "../../Header.h"
#include "../../IO/Serializable.h"

class ChunkData : public Serializable
{
public:
	ChunkData();
	~ChunkData();

	std::string serialize() const;
	bool deserialize(std::string data);

	std::array<bool, Consts::CHUNK_VOLUME> blocks;
};