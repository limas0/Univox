#pragma once
#include "Server\Server.h"
#include "Client\Client.h"

class Packet
{
public:
	Packet();
	~Packet();

	template<typename T>
	void pack();
	virtual void unpack() = 0;

	//virtual bool dispatch(Server *server, Packet *packet) = 0;

public:
	sf::Packet rawPacket;
};

template<typename T>
void Packet::pack()
{
	rawPacket << typeid(T).hash_code();
}