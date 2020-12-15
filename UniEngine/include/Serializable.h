#pragma once
#include "UniEngineAPI.h"

namespace YAML {
	class Emitter;
}

namespace UniEngine
{
	class UNIENGINE_API Serializable
	{
	public:
		virtual void Serialize(YAML::Emitter& out){}
		virtual void Deserialize() {}
	};
}

