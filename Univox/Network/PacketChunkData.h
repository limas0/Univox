#pragma once
#include "Packet.h"
#include "../Math/Math.h"
#include "../World/Chunk/ChunkData.h"

class PacketChunkData : public Packet
{
public:
	PacketChunkData();
	~PacketChunkData();

	void pack();
	void unpack();

	static bool dispatchServer(Server *server, sf::Packet *packet);
	static bool dispatchClient(Client *client, sf::Packet *packet);

	Vec2i index;
	ChunkData chunk;
};
