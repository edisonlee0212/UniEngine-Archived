#pragma once
#include "Misc.h"
namespace UniEngine {
	class Debug
	{
	public:
		static void Log(std::string msg);
		static void Error(std::string msg);
		static std::vector<std::string*> mLogMessages;
		static std::vector<std::string*> mErrorMessages;
	};
	
}