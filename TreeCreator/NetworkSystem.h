#pragma once
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#include <string.h>
#include "UniEngineAPI.h"

namespace UniEngine {
	class NetworkSystem :
		public SystemBase
	{
	private:
		void transferdataToServer();
		void transferDatatoLocal();
	public:
		NetworkSystem();
		void OnCreate();
		void OnDestroy() {};
		void Update() {};
		void FixedUpdate();
		SOCKET socket_address;//might change to pool of socket in the future
		std::queue<std::string> data_queue_local_s;
		std::queue<std::string> data_queue_server_s;
		std::queue<std::string> data_queue_server_r;
		std::queue<std::string> data_queue_local_r;
	};
}

