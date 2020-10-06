#include "pch.h"
#include "Debug.h"
using namespace UniEngine;

std::vector<std::string*> Debug::_Errors;
std::vector<std::string*> Debug::_Logs;
std::mutex Debug::_Mutex;