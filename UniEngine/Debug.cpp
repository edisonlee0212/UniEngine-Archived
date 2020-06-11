#include "pch.h"
#include "Debug.h"
using namespace UniEngine;

void Debug::Log(std::string msg) {
	mLogMessages.push_back(new std::string(msg + "\n"));
}

void Debug::Error(std::string msg) {
	mErrorMessages.push_back(new std::string(msg + "\n"));
}