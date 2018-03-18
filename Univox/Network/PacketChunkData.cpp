#include "PacketChunkData.h"

PacketChunkData::PacketChunkData():
	Packet()
{
}

PacketChunkData::~PacketChunkData()
{
}

void PacketChunkData::pack(std::string msg)
{
	Packet::pack<PacketChunkData>();
	//
	rawPacket << msg;
}

void PacketChunkData::unpack()
{
	rawPacket >> msg;
}

bool PacketChunkData::dispatch(Server *server, sf::Packet *packet)
{
	PacketChunkData pake;
	pake.rawPacket = *packet;
	pake.unpack();

	std::cout << pake.msg << std::endl;

	return true;
}
