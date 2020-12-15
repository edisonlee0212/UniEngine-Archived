#pragma once
#include "UniEngineAPI.h"

namespace UniEngine
{
	class UNIENGINE_API SerializableClass
	{
	public:
		virtual void Serialize(){}
		virtual void Deserialize() {}
	};
}

