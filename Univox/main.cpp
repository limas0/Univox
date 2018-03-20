#include "Network\Server\Server.h"
#include "Network\Client\Client.h"
#include "Header.h"
#include "Game.h"
#include "Network\PacketChunkData.h"

int main()
{
	std::srand(unsigned int(time(NULL)));

	Server server;
	server.create();
	server.run();

	Game game;
	game.create();

	Client client;
	client.create(&game);
	client.connect();
	client.run();

	game.run();
	game.destroy();

	client.destroy();
	server.destroy();

	system("pause");

	return 0;
}