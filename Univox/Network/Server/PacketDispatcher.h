#pragma once
#include <unordered_map>
#include <functional>
#include <iostream>

class Server;
class Packet;
namespace sf { class Packet; }

template<typename U>
class PacketDispatcher
{
public:
	PacketDispatcher();
	~PacketDispatcher();

	void create(U *u);
	void destroy();

	template<typename T>
	inline void registerPacket();

	void dispatchPacket(size_t hashCode, sf::Packet *packet);

private:
	U *p_u = nullptr;
	std::unordered_map<size_t, std::function<bool(U*, sf::Packet*)>> registeredPackets;
};

template<typename U>
PacketDispatcher<U>::PacketDispatcher()
{

}

template<typename U>
PacketDispatcher<U>::~PacketDispatcher()
{

}

template<typename U>
void PacketDispatcher<U>::create(U *u)
{
	p_u = u;
}

template<typename U>
void PacketDispatcher<U>::destroy()
{

}

template<typename U>
template<typename T>
inline void PacketDispatcher<U>::registerPacket()
{
	if constexpr(std::is_same_v<T, Packet>)
		assert(!"Cannot register base Packet");

	if constexpr(std::is_same_v<U, Server>)
		registeredPackets.emplace(typeid(T).hash_code(), &T::dispatchServer);

	else if constexpr(std::is_same_v<U, Client>)
		registeredPackets.emplace(typeid(T).hash_code(), &T::dispatchClient);

	else
		std::cout << "Cannot register packet to " << typeid(U).name() << std::endl;

	std::cout << "Registered " << typeid(T).name() << std::endl;
}

template<typename U>
void PacketDispatcher<U>::dispatchPacket(size_t hashCode, sf::Packet *packet)
{
	auto iter = registeredPackets.find(hashCode);
	if (iter != registeredPackets.end())
	{
		iter->second(p_u, packet);
	}
	else
	{
		std::cout << "Cannot dispatch not registered packet" << std::endl;
	}
}
