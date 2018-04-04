#include "ChunkData.h"
#include "Chunk.h"
#include "..\..\Block\Block.h"
#include "..\..\Block\BlockProperties.h"
#include <execution>
#include "..\..\Utils\Metadata.h"
#include <iostream>

ChunkData::ChunkData()
{
	for (int i = 0; i < blocks.size(); ++i)
	{
		blocks[i].reset(new Block<BlockProperties>());
	}
}

ChunkData::~ChunkData()
{

}

void ChunkData::serialize(ByteBuffer &outData) const
{
	/*int size = 0;
	size = std::accumulate(blocks.begin(), blocks.end(), size_t(0), [&](size_t &r, const std::unique_ptr<IBlock> &l) { return r + l->size(); });
	outData << size;*/

	for (int i = 0; i < blocks.size(); ++i)
	{
		ByteBuffer buffer;
		((Block<BlockProperties>*)blocks[i].get())->metadata.setProperty("into", "w dupe");
		blocks[i]->serialize(buffer);
		outData << buffer;
		//std::memcpy(&outData.buffer[writeLoc], buffer.getBytes(), buffer.getSizeInBytes());
		//writeLoc += buffer.getSizeInBytes();
	}

	//std::cout << size << std::endl;

	//Metadata meta;
	//meta.setProperty("into", "penon");
	////std::cout << meta.setProperty("into", "penon") << std::endl;
	////std::cout << meta.getProperty("into") << std::endl;

	//ByteBuffer sermeta;
	//meta.serialize(sermeta);

	//ByteBuffer gouda;
	//sermeta.compress(gouda);
	////std::cout << sermeta.getSizeInBytes() << std::endl;
	////std::cout << gouda.getSizeInBytes() << std::endl;

	//ByteBuffer lizacja;
	//lizacja.resize(sermeta.getSizeInBytes());
	//gouda.decompress(lizacja);

	////std::cout << lizacja.getSizeInBytes() << std::endl;

	//ByteBuffer temp;
	//temp << lizacja;

	//ByteBuffer akacja;
	//temp >> akacja;

	//Metadata amfa;
	//amfa.deserialize(akacja);

	//std::cout << amfa.getProperty("into") << std::endl;
	//
	////ByteBuffer compressedBuff;
	////buff.compress(compressedBuff);
	////std::cout << buff.getSizeInBytes() << std::endl;
	////std::cout << compressedBuff.getSizeInBytes() << std::endl;
}

bool ChunkData::deserialize(ByteBuffer &inData)
{
	/*int size = 0;
	inData >> size;
	std::cout << size << std::endl;*/

	/*for (int i = 0; i < 1; ++i)
	{
		Metadata met;
		ByteBuffer buffer;
		std::string cos;
		inData >> buffer;
		buffer >> cos;
		met.deserialize(buffer);
		
		int temp = 0;
		buffer >> temp;
		std::cout << met.getProperty("into") << std::endl;
	}*/
	
	return true;
}

void ChunkData::cloneTo(ChunkData &dst)
{
	for (int i = 0; i < blocks.size(); ++i)
	{
		dst.blocks[i].reset(blocks[i]->clone());
	}
}
