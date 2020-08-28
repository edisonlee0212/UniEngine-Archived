#pragma once
#include "NetworkSystem.h"
//#include <Windows.h>

using namespace UniEngine;

void UniEngine::NetworkSystem::OnCreate() {
#pragma region Initial setup
	int a = 0;
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
	sockaddr_in client;
	int clientSize = sizeof(client);
	_Socket = accept(listening, (sockaddr*)&client, &clientSize);
#pragma endregion

#pragma region Sending Thread Setup
	auto sendingFunction = [this]() {
		while (true) {
			std::unique_lock<std::mutex> lock(_SendingQueueMutex);
			_SendingThreadCV.wait(lock);
			//Send all packets in sending queue here.

		}
	};

	auto receivingFunction = [this]() {
		while (true) {
			//std::unique_lock<std::mutex> lock(_ReceivingQueueMutex);
			//_ReceivingThreadCV.wait(lock);
			//Receive packet
		}
	};

	_SendingThread = new std::thread(sendingFunction);
	_ReceivingThread = new std::thread(receivingFunction);
#pragma endregion
	Enable();
}

//transfer the data from local queue to the queue sending data
void UniEngine::NetworkSystem::TransferDataToServer()
{
	if (!_LocalSendingQueue.empty()) {
		std::lock_guard<std::mutex> lock(_SendingQueueMutex);
		if (_ServerSendingQueue.empty()) {
			_LocalSendingQueue.swap(_ServerSendingQueue);
		}
		else {
			while (!_LocalSendingQueue.empty())
			{
				_ServerSendingQueue.push(_LocalSendingQueue.front());
				_LocalSendingQueue.pop();
			}
		}
		_SendingThreadCV.notify_one();
	}
}

void UniEngine::NetworkSystem::TransferDataToLocal()
{
	if (!_ServerReadingQueue.empty()) {
		std::lock_guard<std::mutex> lock(_ReceivingQueueMutex);
		if (_LocalReadingQueue.empty()) {
			_ServerReadingQueue.swap(_LocalReadingQueue);
		}
		else {
			while (!_ServerReadingQueue.empty())
			{
				_LocalReadingQueue.push(_ServerReadingQueue.front());
				_ServerReadingQueue.pop();
			}
		}
		_ReceivingThreadCV.notify_one();
	}
}

void UniEngine::NetworkSystem::FixedUpdate()
{
	TransferDataToServer();
	TransferDataToLocal();
	
	std::vector<std::shared_future<void>> futures;
	futures.push_back(_ThreadPool->Push([this](int id) {
		//std::cout << "Sending........ " << std::endl;
		Debug::Log("Sending........ ");
		//_SendingMutex.lock();
		while (!_ServerSendingQueue.empty())
		{
			//std::cout << "Inside Sending While" << std::endl;
			Debug::Log("Inside Sending While");
			std::string tempstr = _ServerSendingQueue.front();
			send(_Socket, tempstr.c_str(), tempstr.size() + 1, 0);
			std::lock_guard<std::mutex> lock(_SendingMutex);
			_ServerSendingQueue.pop();
		}
		//_SendingMutex.unlock();
		}).share());
	std::cout << "Receiving....... " << std::endl;
	std::queue<std::string> dqsr = _ServerReadingQueue;
	dqsr.push("safasfsd");
	//std::cout << dqsr.front() << std::endl;
	futures.push_back(_ThreadPool->Push([this](int id) {
		while (true)
		{
			Debug::Log("Inside receiving While");
			char buf[4096];
			ZeroMemory(buf, 4096);
			int bytesReceived = recv(_Socket, buf, 4096, 0);
			std::cout << buf << std::endl;
			Debug::Log("Before Put Data in the quene");
			std::lock_guard<std::mutex> lock(_ReceivingMutex);
			_ServerReadingQueue.push(std::string("abc"));
			Debug::Log("After Put Data in the quene");
			if (bytesReceived == SOCKET_ERROR)
			{
				Debug::Error("Error in recv(). Quitting");
				break;
			}

			if (bytesReceived == 0)
			{
				Debug::Error("Client disconnected ");
				break;
			}

			if (bytesReceived == 1)
			{
				Debug::Error("End of data_section, exit loop ");
				break;
			}
		}
		}).share());

	//for (auto i : futures) i.wait(); // do not need to wait

	
}
