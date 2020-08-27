#pragma once
#include "NetworkSystem.h"
//#include <Windows.h>


using namespace UniEngine;
void UniEngine::NetworkSystem::OnCreate() {
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	std::cout << "Sever Start" << std::endl;
	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		std::cerr << "Can't Initialize winsock! Quitting" << std::endl;
		return;
	}
	//int64_t s = socket(address->addr.sa_family, SOCK_DGRAM, IPPROTO_UDP);
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create a socket! Quitting" << std::endl;
		return;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(57000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 
	int off = 0;
	std::cout << "Set Socket opt" << std::endl;
	int result = setsockopt(listening, IPPROTO_IPV6, IPV6_V6ONLY, (char*)&off, sizeof(off));
	if (result != 0)
	{
		//*errorcode = native_get_last_error();
		closesocket(listening);
		return;
	}
	std::cout << "Before Binding" << std::endl;
	bind(listening, (sockaddr*)&hint, sizeof(hint));
	listen(listening, SOMAXCONN);
}

//transfer the data from local queue to the queue sending data
void UniEngine::NetworkSystem::transferdataToServer()
{
	if (data_queue_server_s.empty()) {
		data_queue_local_s.swap(data_queue_server_s);
	}
	else {
		while (!data_queue_local_s.empty())
		{
			data_queue_server_s.push(data_queue_local_s.front());
			data_queue_local_s.pop();
		}
	}
}

void UniEngine::NetworkSystem::transferDatatoLocal()
{
	if (data_queue_local_r.empty()) {
		data_queue_server_r.swap(data_queue_local_r);
	}
	else {
		while (!data_queue_server_r.empty())
		{
			data_queue_local_r.push(data_queue_server_r.front());
			data_queue_server_r.pop();
		}
	}
}

void UniEngine::NetworkSystem::FixedUpdate()
{
	NetworkSystem::transferdataToServer();
	NetworkSystem::transferDatatoLocal();
	std::vector<std::shared_future<void>> futures;
	SOCKET s = NetworkSystem::socket_address;
	std::queue<std::string> dqss = data_queue_server_s;
	std::queue<std::string> dqsr = data_queue_server_r;
	futures.push_back(_ThreadPool->Push([&s,&dqss](int id) {
		while (!dqss.empty())
		{
			std::string tempstr = dqss.front();
			send(s, tempstr.c_str(), tempstr.size() + 1, 0);
			dqss.pop();
		}
	}).share());
	futures.push_back(_ThreadPool->Push([&s, &dqsr](int id) {
		while (true)
		{
			char buf[4096];
			ZeroMemory(buf, 4096);
			int bytesReceived = recv(s, buf, 4096, 0);
			dqsr.push(std::string(buf));
			if (bytesReceived == SOCKET_ERROR)
			{
				std::cerr << "Error in recv(). Quitting" << std::endl;
				break;
			}

			if (bytesReceived == 0)
			{
				std::cout << "Client disconnected " << std::endl;
				break;
			}

			if (bytesReceived == 1)
			{
				std::cout << "End of data_section, exit loop " << std::endl;
				break;
			}
		}
	}).share());

	//for (auto i : futures) i.wait(); // do not need to wait
}
