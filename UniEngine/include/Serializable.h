#pragma once
#include "UniEngineAPI.h"

namespace UniEngine
{
	class UNIENGINE_API Serializable
	{
	public:
		virtual void Serialize(){}
		virtual void Deserialize() {}
	};
}

