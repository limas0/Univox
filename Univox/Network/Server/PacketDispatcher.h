#pragma once
#include <unordered_map>
#include <functional>
#include <iostream>

class Server;
class Packet;
namespace sf { class Packet; }

class PacketDispatcher
{
public:
	PacketDispatcher();
	~PacketDispatcher();

	void create(Server *server);
	void destroy();

	template<typename T>
	inline void registerPacket();

	void dispatchPacket(size_t hashCode, sf::Packet *packet);

private:
	Server * p_server = nullptr;
	std::unordered_map<size_t, std::function<bool(Server*, sf::Packet*)>> registeredPackets;
};

template<typename T>
inline void PacketDispatcher::registerPacket()
{
	//T::id = registeredPackets.size();
	registeredPackets.emplace(typeid(T).hash_code(), &T::dispatch);

	std::cout << "Registered " << typeid(T).name() << std::endl;
}

template<>
inline void PacketDispatcher::registerPacket<Packet>()
{
	std::cout << "Cannot register base Packet" << std::endl;
}
