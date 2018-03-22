#include "ChunkData.h"
#include "Chunk.h"

ChunkData::ChunkData()
{
}

ChunkData::~ChunkData()
{
}

void ChunkData::serialize(ByteBuffer &outData) const
{
	outData.resize(blocks.size() * sizeof(decltype(blocks)::value_type));
	outData.toBytes(&blocks[0]);
}

bool ChunkData::deserialize(ByteBuffer &inData)
{
	if (inData.getSizeInBytes() == blocks.size() * sizeof(decltype(blocks)::value_type))
	{
		inData.fromBytes(&blocks[0]);
		return true;
	}
	
	return false;
}