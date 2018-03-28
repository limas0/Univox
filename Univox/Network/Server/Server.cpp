#include "Server.h"
#include "../PacketChunkData.h"
#include "../../World/WorldConstants.h"
#include "../../World/Chunk/Chunk.h"

Server::Server()
{

}

Server::~Server()
{

}

void Server::create()
{
	dispatcher.create(this);
	dispatcher.registerPacket<PacketChunkData>();
}

void Server::destroy()
{
	isRunning = false;

	if(mainThread)
		mainThread->join();

	delete mainThread;
	mainThread = nullptr;

	dispatcher.destroy();
}

void Server::run()
{
	isRunning = true;
	mainThread = new std::thread(&Server::loop, this);
}

void Server::loop()
{
	tcpListener.listen(Consts::SERVER_TCP_PORT);
	udpSocket.bind(Consts::SERVER_UDP_PORT);

	selector.add(tcpListener);
	selector.add(udpSocket);

	while (isRunning)
	{
		if (selector.wait(sf::milliseconds(1000)))
		{
			if (selector.isReady(tcpListener))
			{
				newConnection();
			}
			else
			{
				for (auto it = tcpClients.begin(); it != tcpClients.end(); ++it)
				{
					receivePacketTCP(*it);
				}

				if (selector.isReady(udpSocket))
				{
					receivePacketUDP();
				}

				updateClients();
			}
		}

		if (tcpClients.size() > 0)
		{
			static int el = 0;

			PacketChunkData test;
			test.index = { 0, 0 };

			for (int i = 0; i < Consts::CHUNK_SIZE; i++)
			{
				for (int j = 0; j < Consts::CHUNK_HEIGHT; j++)
				{
					for (int k = 0; k < Consts::CHUNK_SIZE; k++)
					{
						test.chunk.blocks[Chunk::translateIndex(i, j, k)] = el == j;
					}
				}
			}

			test.pack();

			for (auto it = tcpClients.begin(); it != tcpClients.end(); ++it)
				(*it)->send(test.rawPacket);

			std::cout << "Sent packet[size: " << test.rawPacket.getDataSize() << "]" << std::endl;

			el += 1;
			el = el % (Consts::CHUNK_HEIGHT - 1);
		}
	}

	disconnectAll();
	updateClients();
}

void Server::newConnection()
{
	sf::TcpSocket *newClient = new sf::TcpSocket();
	if (tcpListener.accept(*newClient) == sf::Socket::Done)
	{
		std::cout << "New connection [" << newClient->getRemoteAddress() << "]" << std::endl;
		addClient(newClient);
	}
	else
	{
		delete newClient;
	}
}

void Server::updateClients()
{
	tcpClients.remove_if([](sf::TcpSocket* client)
	{
		bool result = client->getRemoteAddress() == sf::IpAddress::None;
		if (result)
		{
			std::cout << "Removed disconnected client" << std::endl;
		}
		return result;
	});
}

void Server::disconnectAll()
{
	for (auto client : tcpClients)
		removeClient(client);

	udpSocket.unbind();
	tcpListener.close();
}

void Server::handlePacket(sf::Packet *packet)
{
	size_t hashCode;
	*packet >> hashCode;
	std::cout << "Received packet[" << hashCode << "]" << std::endl;
	
	dispatcher.dispatchPacket(hashCode, packet);

	delete packet;
	packet = nullptr;
}

void Server::addClient(sf::TcpSocket *client)
{
	tcpClients.push_back(client);
	selector.add(*client);
}

void Server::removeClient(sf::TcpSocket *client)
{
	client->disconnect();
	selector.remove(*client);

	std::cout << "Server closed connection with client" << std::endl;
}

void Server::receivePacketTCP(sf::TcpSocket *client)
{
	if (selector.isReady(*client))
	{
		sf::Packet *packet = new sf::Packet();
		sf::Socket::Status status = client->receive(*packet);
		if (status == sf::Socket::Done)
		{
			handlePacket(packet);
		}
		else if (status == sf::Socket::Status::Disconnected)
		{
			std::cout << "Client disconnected" << std::endl;
			removeClient(client);

			delete packet;
			packet = nullptr;
		}
		else
		{
			delete packet;
			packet = nullptr;
		}
	}
}

void Server::receivePacketUDP()
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
