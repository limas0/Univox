#pragma once
#include <thread>
#include <memory>
#include <iostream>
#include <atomic>
#include <chrono>
#include <array>

#include <SFML\Network.hpp>

#include "..\Server\ServerConstants.h"
#include "..\Server\PacketDispatcher.h"

class Game;

class Client
{
public:
	Client();
	~Client();

	void create(Game *game);
	void destroy();

	void run();
	void loop();

	void connect();
	void disconnect();

	Game *getGame() const;
private:
	void checkConnection();
	void handlePacket(sf::Packet *packet);

	void receivePacketTCP();
	void receivePacketUDP();

	Game *p_game = nullptr;

	std::atomic<bool> isRunning = false;
	std::thread *mainThread = nullptr;

	sf::SocketSelector selector;
	sf::TcpSocket tcpSocket;
	sf::UdpSocket udpSocket;

	PacketDispatcher<Client> dispatcher;
};