
#pragma once
#include "CoreAPI.h"
namespace UniEngine {
	class CORE_API Debug
	{
	public:
		static void Log(std::string msg);
		static void Error(std::string msg);
		static std::vector<std::string*> mLogMessages;
		static std::vector<std::string*> mErrorMessages;
	};

}