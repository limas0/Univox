#include "PacketDispatcher.h"

PacketDispatcher::PacketDispatcher()
{

}

PacketDispatcher::~PacketDispatcher()
{

}

void PacketDispatcher::create(Server *server)
{
	p_server = server;
}

void PacketDispatcher::destroy()
{

}

void PacketDispatcher::dispatchPacket(size_t hashCode, sf::Packet *packet)
{
	auto iter = registeredPackets.find(hashCode);
	if (iter != registeredPackets.end())
	{
		iter->second(p_server, packet);
	}
	else
	{
		std::cout << "Cannot dispatch not registered packet" << std::endl;
	}
}
