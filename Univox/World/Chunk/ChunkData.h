#pragma once
#include "../../Header.h"
#include "../../IO/Serializable.h"

class IBlock;

class ChunkData : public Serializable
{
public:
	ChunkData();
	~ChunkData();

	void serialize(ByteBuffer &outData) const;
	bool deserialize(ByteBuffer &inData);

	void cloneTo(ChunkData &dst);

	std::array<std::unique_ptr<IBlock>, Consts::CHUNK_VOLUME> blocks;
};