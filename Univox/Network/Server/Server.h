#pragma once
#include <thread>
#include <memory>
#include <iostream>
#include <atomic>
#include <chrono>
#include <array>

#include <SFML\Network.hpp>

#include "ServerConstants.h"
#include "PacketDispatcher.h"

class Server
{
public:
	Server();
	~Server();

	void create();
	void destroy();

	void run();
	void loop();
private:
	void newConnection();
	void updateClients();
	void disconnectAll();
	void handlePacket(sf::Packet *packet);

	void addClient(sf::TcpSocket *client);
	void removeClient(sf::TcpSocket *client);

	void receivePacketTCP(sf::TcpSocket *client);
	void receivePacketUDP();

	std::atomic<bool> isRunning = false;
	std::thread *mainThread = nullptr;

	sf::SocketSelector selector;
	sf::TcpListener tcpListener;
	sf::UdpSocket udpSocket;
	std::list<sf::TcpSocket*> tcpClients;

	PacketDispatcher dispatcher;
};