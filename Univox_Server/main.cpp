#include <iostream>
#include <array>
#include <Poco\Net\TCPServer.h>

class Connection : public Poco::Net::TCPServerConnection
{
public:
	Connection(const Poco::Net::StreamSocket &socket) :
		Poco::Net::TCPServerConnection(socket)
	{

	}

	void run()
	{
		std::cout << "New connection [" << socket().peerAddress().host().toString() << "]" << std::endl;
		std::vector<int> buffer;

		for (int i = 0; i < 16; i++)
		{
			buffer.push_back(std::rand() % 10);
			std::cout << buffer.back() << std::endl;
		}

		socket().sendBytes(buffer.data(), buffer.size() * sizeof(int));
	}
};

int main()
{
	Poco::Net::ServerSocket serverSocket(1234);

	Poco::Net::TCPServerParams *serverParams = new Poco::Net::TCPServerParams();
	serverParams->setMaxThreads(4);
	serverParams->setMaxQueued(4);
	serverParams->setThreadIdleTime(100);

	Poco::Net::TCPServer server(new Poco::Net::TCPServerConnectionFactoryImpl<Connection>, serverSocket, serverParams);
	server.start();
	
	Poco::Net::SocketAddress address("127.0.0.1", server.port());

	Poco::Net::StreamSocket client;
	client.connect(address);

	std::array<int, 16> buffer;
	int size = client.receiveBytes(buffer.data(), sizeof(int) * buffer.size());
	std::cout << "size: " << size << std::endl;
	for (int i = 0; i < buffer.size(); i++)
	{
		std::cout << buffer[i] << std::endl;
	}

	while (true);

	return 0;
}