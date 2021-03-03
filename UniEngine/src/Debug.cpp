#include "pch.h"
#include "Debug.h"

#include "UniEngine.h"
using namespace UniEngine;

std::vector<ConsoleMessage> Debug::_consoleMessages;
std::mutex Debug::_consoleMessageMutex;
void Debug::Log(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(_consoleMessageMutex);
	ConsoleMessage cm;
	cm.m_value = msg;
	cm.m_type = ConsoleMessageType::Log;
	cm.m_time = Application::EngineTime();
	_consoleMessages.push_back(cm);
}

void Debug::Error(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(_consoleMessageMutex);
	std::cout << msg << "\n" << std::endl;
	ConsoleMessage cm;
	cm.m_value = msg;
	cm.m_type = ConsoleMessageType::Error;
	cm.m_time = Application::EngineTime();
	_consoleMessages.push_back(cm);
}

void Debug::Warning(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(_consoleMessageMutex);
	ConsoleMessage cm;
	cm.m_value = msg;
	cm.m_type = ConsoleMessageType::Warning;
	cm.m_time = Application::EngineTime();
	_consoleMessages.push_back(cm);
}

std::vector<ConsoleMessage>& Debug::GetConsoleMessages()
{
	return _consoleMessages;
}