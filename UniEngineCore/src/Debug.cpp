#include "Debug.h"
using namespace UniEngine;
std::vector<std::string*> Debug::mErrorMessages;
std::vector<std::string*> Debug::mLogMessages;

void Debug::Log(std::string msg) {
	mLogMessages.push_back(new std::string(msg + "\n"));
}

void Debug::Error(std::string msg) {
	mErrorMessages.push_back(new std::string(msg + "\n"));
}