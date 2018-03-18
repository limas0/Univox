//#pragma once
//#include <Poco\Net\TCPServer.h>
//
//class TCPServerConnection : public Poco::Net::TCPServerConnection
//{
//public:
//	TCPServerConnection(const Poco::Net::StreamSocket &socket) :
//		Poco::Net::TCPServerConnection(socket)
//	{
//
//	}
//
//	void run()
//	{
//		std::cout << "New connection [" << socket().peerAddress().host().toString() << "]" << std::endl;
//		std::vector<int> buffer;
//
//		for (int i = 0; i < 16; i++)
//		{
//			buffer.push_back(std::rand() % 10);
//			std::cout << buffer.back() << std::endl;
//		}
//
//		bool isRunning = true;
//		int receiveSize = 0;
//
//		while (isRunning)
//		{
//			
//			receiveSize = socket().receiveBytes(nullptr, 0);
//			socket().sendBytes(buffer.data(), buffer.size() * sizeof(int));
//			std::cout << "Receiving" << std::endl;
//
//			isRunning = receiveSize > 0;
//		}
//	}
//};