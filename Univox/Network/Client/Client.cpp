#include "Client.h"
#include "../PacketChunkData.h"

Client::Client()
{
}

Client::~Client()
{
}

void Client::create(Game *game)
{
	p_game = game;

	dispatcher.create(this);
	dispatcher.registerPacket<PacketChunkData>();
}

void Client::destroy()
{
	isRunning = false;

	if (mainThread)
		mainThread->join();

	delete mainThread;
	mainThread = nullptr;

	dispatcher.destroy();
}

void Client::run()
{
	isRunning = true;
	mainThread = new std::thread(&Client::loop, this);
}

void Client::loop()
{
	selector.add(tcpSocket);
	selector.add(udpSocket);

	while (isRunning)
	{
		checkConnection();

		if (selector.wait(sf::seconds(1)))
		{
			if (selector.isReady(tcpSocket))
			{
				receivePacketTCP();
			}

			if (selector.isReady(udpSocket))
			{
				receivePacketUDP();
			}
		}
	}

	udpSocket.unbind();
	tcpSocket.disconnect();
}

void Client::connect()
{
	tcpSocket.connect("localhost", Consts::SERVER_TCP_PORT);
	udpSocket.bind(Consts::CLIENT_UDP_PORT);
}

void Client::disconnect()
{
	udpSocket.unbind();
	tcpSocket.disconnect();
}

Game *Client::getGame() const
{
	return p_game;
}

void Client::checkConnection()
{
	if (tcpSocket.getRemoteAddress() == sf::IpAddress::None)
		std::cout << "noconnection" << std::endl;
}

void Client::handlePacket(sf::Packet *packet)
{
	size_t hashCode;
	*packet >> hashCode;
	//std::cout << "Received packet[" << hashCode << "]" << std::endl;

	dispatcher.dispatchPacket(hashCode, packet);

	delete packet;
	packet = nullptr;
}

void Client::receivePacketTCP()
{
	sf::Packet *packet = new sf::Packet();
	sf::Socket::Status status = tcpSocket.receive(*packet);
	if (status == sf::Socket::Done)
	{
		handlePacket(packet);
	}
	else if (status == sf::Socket::Status::Disconnected)
	{
		std::cout << "No connection to server" << std::endl;

		delete packet;
		packet = nullptr;
	}
	else
	{
		delete packet;
		packet = nullptr;
	}
}

void Client::receivePacketUDP()
{
	sf::IpAddress ip;
	unsigned short port;
	sf::Packet *packet = new sf::Packet();
	if (udpSocket.receive(*packet, ip, port) == sf::Socket::Done)
	{
		handlePacket(packet);
	}
	else
	{
		delete packet;
		packet = nullptr;
	}
}
