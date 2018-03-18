#include "Network\Server\Server.h"
#include "Header.h"
#include "Game.h"
#include "Network\PacketChunkData.h"

int main()
{
	std::srand(unsigned int(time(NULL)));

	Server server;
	server.create();
	server.run();

	sf::TcpSocket socket;
	socket.connect("127.0.0.1", Consts::SERVER_TCP_PORT);

	sf::UdpSocket udp;
	udp.bind(Consts::CLIENT_UDP_PORT);

	PacketChunkData test;
	test.pack("GOLZEB DIEDIEDIEDIEDIEDIEDIE");

	udp.send(test.rawPacket, "127.0.0.1", Consts::SERVER_UDP_PORT);

	Game game;
	game.create();
	game.run();
	game.destroy();

	server.destroy();

	system("pause");

	return 0;
}