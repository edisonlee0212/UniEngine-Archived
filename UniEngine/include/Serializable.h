#pragma once
#include "UniEngineAPI.h"

namespace YAML {
	class Emitter;
	class Node;
}

namespace UniEngine
{
	class UNIENGINE_API Serializable
	{
	public:
		virtual ~Serializable() = default;
		virtual void Serialize(YAML::Emitter& out){}
		virtual void Deserialize(const YAML::Node& in) {}
	};
}

