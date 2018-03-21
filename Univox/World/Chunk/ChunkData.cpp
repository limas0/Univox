#include "ChunkData.h"
#include "Chunk.h"

ChunkData::ChunkData()
{
}

ChunkData::~ChunkData()
{
}

//void *ChunkData::serialize() const
//{
//	//std::stringstream buffer;
//
//	//for (int i = 0; i < Consts::CHUNK_SIZE; i++)
//	//{
//	//	for (int j = 0; j < Consts::CHUNK_HEIGHT; j++)
//	//	{
//	//		for (int k = 0; k < Consts::CHUNK_SIZE; k++)
//	//		{
//	//			buffer << blocks[Chunk::translateIndex(i, j, k)] << " ";
//	//		}
//	//	}
//	//}
//
//	////std::cout << buffer.str() << std::endl;
//
//	//return buffer.str();
//	return (void*)blocks.data();
//}

std::string ChunkData::serialize() const
{
	std::stringstream buffer;

	for (int i = 0; i < Consts::CHUNK_VOLUME; i++)
	{
		buffer << blocks[i] << " ";
	}

	//std::cout << buffer.str() << std::endl;

	return buffer.str();
}

bool ChunkData::deserialize(std::string & data)
{
	std::stringstream buffer(data);
	bool block = false;
	int index = 0;

	while (buffer >> block)
	{
		blocks[index] = block;
		index++;
	}

	return true;
}

//bool ChunkData::deserialize(void *data)
//{
//	/*std::stringstream buffer(data);
//	bool block = false;
//	int index = 0;
//
//	while (buffer >> block)
//	{
//		blocks[index] = block;
//		index++;
//	}
//
//	return true;*/
//	std::memcpy(blocks.data(), data, sizeof(bool) * blocks.size());
//	return true;
//}
