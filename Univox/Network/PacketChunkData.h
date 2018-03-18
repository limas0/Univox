#pragma once
#include "Packet.h"

class PacketChunkData : public Packet
{
public:
	PacketChunkData();
	~PacketChunkData();

	void pack(std::string msg);
	void unpack();

	static bool dispatch(Server *server, sf::Packet *packet);

private:
	std::string msg;
};
