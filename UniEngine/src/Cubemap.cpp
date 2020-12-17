#include "pch.h"
#include "Cubemap.h"

UniEngine::Cubemap::Cubemap()
{
	Name = "New Cubemap";
}

std::vector<std::string> UniEngine::Cubemap::Paths() const
{
	return _Paths;
}
