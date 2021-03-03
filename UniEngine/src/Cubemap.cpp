#include "pch.h"
#include "Cubemap.h"

UniEngine::Cubemap::Cubemap()
{
	m_name = "New Cubemap";
}

std::vector<std::string> UniEngine::Cubemap::Paths() const
{
	return _Paths;
}
