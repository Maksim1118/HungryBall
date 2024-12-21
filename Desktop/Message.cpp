#include "Message.h"

Message message;

Message::Message()
{
	//sf::Socket::Status status = socket.connect("127.0.0.1", 2040);
	//if (status != sf::Socket::Done)
	//{
	//	// error...
	//}
}

Message::~Message()
{
	/*socket.disconnect();*/
}

nlohmann::json Message::process(nlohmann::json request)
{
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("127.0.0.1", 2040);
	if (status != sf::Socket::Done)
	{
		// error...
	}

	string data = request.dump();
	/*std::cout << "Send " << data << std::endl;*/

	// TCP socket:
	if (socket.send(data.c_str(), data.size() + 1) != sf::Socket::Done)
	{
		// error...
	}

	char data2[65536];
	std::size_t received = 0;
	// TCP socket:

	if (socket.receive(data2, 65536, received) != sf::Socket::Done)
	{
			// error...
	}
	
	
	if (!received)
	{
		data2[0] = 0;
	}
	//std::cout << "Received " << received << " bytes" << std::endl;
	//std::cout << "Text " << data2 << std::endl;
	socket.disconnect();
	nlohmann::json response;
	try
	{
		response = nlohmann::json::parse(data2);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		cerr << "Error parsing JSON: " << e.what() << endl;
	}

	return response;
	//{
	//	lock_guard<mutex> lock(m);
	//	messageServer.request = request;
	//	messageServer.isResponse = false;
	//}
	
	/*while (1)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		{
			lock_guard<mutex> lock(m);
			if (messageServer.isResponse)
			{
				return  messageServer.response;		
			}
		}

	}*/
	//sf::TcpSocket socket;
	//sf::Socket::Status status = socket.connect("127.0.0.1", 2040);
	//if (status != sf::Socket::Done)
	//{
	//	// error...
	//}

	//char* data = "Hello";

	//// TCP socket:
	//if (socket.send(data, strlen(data) + 1) != sf::Socket::Done)
	//{
	//	// error...
	//}

	//char data2[100];
	//std::size_t received;

	//// TCP socket:
	//if (socket.receive(data2, 100, received) != sf::Socket::Done)
	//{
	//	// error...
	//}
	//std::cout << "Received " << received << " bytes" << std::endl;
	//std::cout << "Text " << data2 << std::endl;
	//socket.disconnect();

}

//int main() {
//	sf::TcpSocket socket;
//	sf::Socket::Status status = socket.connect("127.0.0.1", 2040);
//	if (status != sf::Socket::Done)
//	{
//		// error...
//	}
//
//	char* data = "Hello";
//
//	// TCP socket:
//	if (socket.send(data, strlen(data) + 1) != sf::Socket::Done)
//	{
//		// error...
//	}
//
//	char data2[100];
//	std::size_t received;
//
//	// TCP socket:
//	if (socket.receive(data2, 100, received) != sf::Socket::Done)
//	{
//		// error...
//	}
//	std::cout << "Received " << received << " bytes" << std::endl;
//	std::cout << "Text " << data2 << std::endl;
//
//	socket.disconnect();
//
//	return 0;
//}