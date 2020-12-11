#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	enum class ConsoleMessageType
	{
		Log, Warning, Error
	};
	struct ConsoleMessage
	{
		ConsoleMessageType Type;
		std::string Value;
		double Time;
	};
	class UNIENGINE_API Debug
	{
		static std::vector<ConsoleMessage> _ConsoleMessages;
		static std::mutex _ConsoleMessageMutex;
	public:
		static void Log(const std::string& msg);
		static void Error(const std::string& msg);
		static void Warning(const std::string& msg);
		static std::vector<ConsoleMessage>& GetConsoleMessages();
	};

}