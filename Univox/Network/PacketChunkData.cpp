#include "PacketChunkData.h"
#include "../Game.h"
#include "../World/Chunk/ChunkMeshBuilder.h"
#include "../Utils/ByteBuffer.h"

PacketChunkData::PacketChunkData():
	Packet()
{
}

PacketChunkData::~PacketChunkData()
{
}

void PacketChunkData::pack()
{
	WE::Timer timer;
	timer.start();

	Packet::pack<PacketChunkData>();
	
	//rawPacket << index.x << index.y;

	ByteBuffer data;
	chunk.serialize(data);
	
	ByteBuffer compressed;
	data.compress(compressed);

	std::cout << "Uncompressed: " << data.getSizeInBytes() / 1000000.f << "MB" << std::endl;
	std::cout << "Uncompressed: " << compressed.getSizeInBytes() / 1000000.f << "MB" << std::endl;

	rawPacket << sf::Uint32(data.getSizeInBytes());
	rawPacket << sf::Uint32(compressed.getSizeInBytes());
	rawPacket.append(compressed.getBytes(), compressed.getSizeInBytes());

	std::cout << "PacketChunkData packed in " << timer.stop() << "ms" << std::endl;
}

sf::Packet &operator>>(sf::Packet &packet, ByteBuffer &buffer)
{
	sf::Uint32 size;
	packet >> size;
	buffer.resize(size);
	std::memcpy(&buffer.buffer[0], &packet.m_data[packet.m_readPos], size);
	packet.m_readPos += size;
	return packet;
}

void PacketChunkData::unpack()
{
	WE::Timer timer;
	timer.start();

	//rawPacket >> index.x >> index.y;
	//std::string data;//DO NOT COUT | NO NULL TERMINATOR
	//rawPacket >> data;

	ByteBuffer buffer;
	//buffer.fromString(data);

	sf::Uint32 decompressedSize = 0;
	rawPacket >> decompressedSize;
	rawPacket >> buffer;
	
	ByteBuffer decompressed(decompressedSize);
	buffer.decompress(decompressed);

	chunk.deserialize(decompressed);

	std::cout << "PacketChunkData unpacked in " << timer.stop() << "ms" << std::endl;
}

bool PacketChunkData::dispatchServer(Server *server, sf::Packet *packet)
{
	PacketChunkData pake;
	pake.rawPacket = *packet;
	pake.unpack();

	std::cout << pake.index.x << pake.index.y << std::endl;

	return true;
}

bool PacketChunkData::dispatchClient(Client *client, sf::Packet *packet)
{
	PacketChunkData pake;
	pake.rawPacket = *packet;
	pake.unpack();

	//std::cout << pake.index.x << pake.index.y << std::endl;

	if (!client)
	{
		std::cout << "[ERROR] Client is nullptr" << std::endl;
		return false;
	}

	if (!client->getGame())
	{
		std::cout << "[ERROR] Game is nullptr" << std::endl;
		return false;
	}
		
	if (!WE::Engine::engine)
	{
		std::cout << "[ERROR] ENGINE is nullptr" << std::endl;
		return false;
	}

	auto chunk = client->getGame()->getWorld().getChunk(pake.index);

	chunk->setChunkData(pake.chunk);

	ChunkMesh *chunkMesh = new ChunkMesh();
	ChunkMeshBuilder(chunk, chunkMesh).build();
	chunkMesh->create(pake.index);

	chunkMesh->setMaterial("Default");
	chunkMesh->setTranslation({ float(pake.index.x * Consts::CHUNK_SIZE), 0.f, float(pake.index.y * Consts::CHUNK_SIZE) });

	client->getGame()->getWorldRenderer().setChunkMesh(chunkMesh);

	return true;
}
