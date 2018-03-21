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

	//constexpr int size = Consts::CHUNK_VOLUME;

	//std::array<float, size> in;
	//for (auto &v : in)
	//{
	//	v = 3.14f;
	//	//std::cout << v << std::endl;
	//}

	//WE::Timer timer;
	//timer.start();

	//std::vector<char> *mid = toBytes(in.data(), in.size());

	//std::array<float, size> out;
	//fromBytes(&(*mid)[0], mid->size(), &out[0]);

	//std::cout << timer.stop() << " ms" << std::endl;

	//std::cout << out[12626] << std::endl;

	system("pause");

	return 0;
}