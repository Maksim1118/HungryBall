#include "MessageServer.h"

MessageServer messageServer;
mutex m;

MessageServer::MessageServer()
{

}

MessageServer::~MessageServer()
{

}

//nlohmann::json MessageServer::process(nlohmann::json request)
//{
//	lock_guard<mutex> lock(m);
//	message.request = request;
//	message.isResponse = false;
//
//
//	nlohmann::json response;
//	while (1)
//	{
//		this_thread::sleep_for(chrono::milliseconds(10));
//		{
//			lock_guard<mutex> lock(m);
//			if (message.isResponse)
//			{
//				response = message.response;
//				break;
//			}
//		}
//
//	}
//}