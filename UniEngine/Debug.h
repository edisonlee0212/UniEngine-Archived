
#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UECORE_API Debug
	{
	public:
		static void Log(std::string msg);
		static void Error(std::string msg);
		static std::vector<std::string*> mLogMessages;
		static std::vector<std::string*> mErrorMessages;
	};

}