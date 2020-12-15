#pragma once
#include "Core.h"

namespace UniEngine
{
	class UNIENGINE_API SerializationManager : public Singleton<SerializationManager>
	{
	public:
		static void Serialize(std::unique_ptr<World>& world, const std::string& path);
		static void Deserialize(std::unique_ptr<World>& world, const std::string& path);
	};
}
