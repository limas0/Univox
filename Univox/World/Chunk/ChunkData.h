#pragma once
#include "../../Header.h"
#include "../../IO/Serializable.h"

class ChunkData : public Serializable
{
public:
	ChunkData();
	~ChunkData();

	void serialize(ByteBuffer &outData) const;
	bool deserialize(ByteBuffer &inData);

	std::array<bool, Consts::CHUNK_VOLUME> blocks;
};