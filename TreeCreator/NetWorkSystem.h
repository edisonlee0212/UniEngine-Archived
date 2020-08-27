#pragma once
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#include <string.h>
#include "UniEngineAPI.h"

namespace UniEngine {
	class UNIENGINE_API NetworkSystem :
		public SystemBase
	{
		void OnCreate();
		void OnDestroy();
		void Update();
		void FixedUpdate();
	public:
		SOCKET socket_address;//might change to pool of socket in the future
		std::queue<std::string> data_queue_local;
		std::queue<std::string> data_queue_server;
		std::queue<std::string> data_queue_receive;
	private:
		void transferdata();
	};
}

