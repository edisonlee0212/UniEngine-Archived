#include "pch.h"
#include "Debug.h"

#include "UniEngine.h"
using namespace UniEngine;

std::vector<ConsoleMessage> Debug::_ConsoleMessages;
std::mutex Debug::_ConsoleMessageMutex;
void Debug::Log(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(_ConsoleMessageMutex);
	ConsoleMessage cm;
	cm.Value = msg;
	cm.Type = ConsoleMessageType::Log;
	cm.Time = Application::EngineTime();
	_ConsoleMessages.push_back(cm);
}

void Debug::Error(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(_ConsoleMessageMutex);
	std::cout << msg << "\n" << std::endl;
	ConsoleMessage cm;
	cm.Value = msg;
	cm.Type = ConsoleMessageType::Error;
	cm.Time = Application::EngineTime();
	_ConsoleMessages.push_back(cm);
}

void Debug::Warning(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(_ConsoleMessageMutex);
	ConsoleMessage cm;
	cm.Value = msg;
	cm.Type = ConsoleMessageType::Warning;
	cm.Time = Application::EngineTime();
	_ConsoleMessages.push_back(cm);
}

std::vector<ConsoleMessage>& Debug::GetConsoleMessages()
{
	return _ConsoleMessages;
}