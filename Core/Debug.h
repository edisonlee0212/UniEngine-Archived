
#pragma once
#include "CoreAPI.h"
namespace UniEngine {
	class CORE_API Debug
	{
		static std::vector<std::string*> _Logs;
		static std::vector<std::string*> _Errors;
		static std::mutex _Mutex;
	public:
		static void Log(std::string msg) {
			std::lock_guard<std::mutex> lock(_Mutex);
			_Logs.push_back(new std::string(msg + "\n"));
		}
		static void Error(std::string msg) {
			std::lock_guard<std::mutex> lock(_Mutex);
			_Errors.push_back(new std::string(msg + "\n"));
		}
		static std::vector<std::string*>* GetLogs() {
			return &_Logs;
		}
		static std::vector<std::string*>* GetErrors() {
			return &_Errors;
		}
	};

}