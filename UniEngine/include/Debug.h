#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	enum class ConsoleMessageType
	{
		Log, Warning, Error
	};
	struct ConsoleMessage
	{
		ConsoleMessageType m_type = ConsoleMessageType::Log;
		std::string m_value = "";
		double m_time = 0;
	};
	class UNIENGINE_API Debug
	{
		static std::vector<ConsoleMessage> _consoleMessages;
		static std::mutex _consoleMessageMutex;
	public:
		static void Log(const std::string& msg);
		static void Error(const std::string& msg);
		static void Warning(const std::string& msg);
		static std::vector<ConsoleMessage>& GetConsoleMessages();
	};

}