#include "PacketChunkData.h"
#include "../Game.h"
#include "../World/Chunk/ChunkMeshBuilder.h"

PacketChunkData::PacketChunkData():
	Packet()
{
}

PacketChunkData::~PacketChunkData()
{
}

void PacketChunkData::pack()
{
	Packet::pack<PacketChunkData>();
	
	rawPacket << index.x << index.y;
	rawPacket << chunk.serialize();
}

void PacketChunkData::unpack()
{
	rawPacket >> index.x >> index.y;
	std::string chunkData;
	rawPacket >> chunkData;
	chunk.deserialize(chunkData);
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

	std::cout << pake.index.x << pake.index.y << std::endl;

	auto chunk = client->getGame()->getWorld().getChunk(pake.index);

	chunk->setChunkData(pake.chunk);

	ChunkMesh *chunkMesh = new ChunkMesh();
	ChunkMeshBuilder(chunk, chunkMesh).build();
	chunkMesh->create();

	chunkMesh->setMaterial("Default");
	chunkMesh->setTranslation({ float(pake.index.x * Consts::CHUNK_SIZE), 0.f, float(pake.index.y * Consts::CHUNK_SIZE) });

	client->getGame()->getWorldRenderer().setChunkMesh(pake.index, chunkMesh);

	return true;
}
