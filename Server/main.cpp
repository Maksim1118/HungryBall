
#include <SFML/Network.hpp>
#include <thread>
#include <iostream>
#include <string.h>
#include "GameEngine.h"
#include "MessageServer.h"
using namespace std;


void listen()
{
	sf::TcpListener listener;

	// bind the listener to a port
	if (listener.listen(2040) != sf::Socket::Done)
	{
		std::cout << "can't create socket" << std::endl;
		exit(-1);
	}
	//sf::TcpListener listener;
	//for (unsigned int port = 1024; port <= 65535; ++port)
	//{
	//	if (listener.listen(port) == sf::Socket::Done)
	//	{
	//		break;
	//	}
	//	if (port == 65535)
	//	{
	//		std::cout << "can't create socket" << std::endl;
	//		return -1;
	//	}
	//}

	while (1)
	{
		sf::TcpSocket socket;
		if (listener.accept(socket) != sf::Socket::Done)
		{
			printf("Error\n");
		}

		char data[65536];
		std::size_t received = 0;

		// TCP socket:
		if (socket.receive(data, 65536, received) != sf::Socket::Done)
		{
			// error...
		}
		/*std::cout << "Received " << received << " bytes" << std::endl;
		std::cout << "Text " << data << std::endl;*/

		{
			lock_guard<mutex> lock(m);
			try
			{
				messageServer.request = nlohmann::json::parse(data);
			}
			catch(const nlohmann::json::parse_error& e)
			{
				cerr << "Error parsing JSON: " << e.what() << endl;
			}
			
			messageServer.isResponse = false;
		}

		while (1)
		{
			this_thread::sleep_for(chrono::milliseconds(10));
			{
				lock_guard<mutex> lock(m);
				if (messageServer.isResponse)
				{
					string data2 = messageServer.response.dump();		

					// TCP socket:
					if (socket.send(data2.c_str(), data2.size() + 1) != sf::Socket::Done)
					{
						// error...
					}
					break;
				}
			}

		}

		socket.disconnect();
	}
}

int main() {
	
	thread server(Server::runServer);
	thread t(listen);
	server.join();
	t.detach();
	// accept a new connection

	return 0;
}