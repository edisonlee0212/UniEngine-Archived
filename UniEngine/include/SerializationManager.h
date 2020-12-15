#pragma once
#include "Core.h"

namespace YAML {
	class Node;
	class Emitter;
}

namespace UniEngine
{
	class UNIENGINE_API SerializationManager : public Singleton<SerializationManager>
	{
		std::unordered_map<size_t, std::function<std::string(ComponentBase*)>> _ComponentDataSerializers;
		static void SerializeEntity(std::unique_ptr<World>& world, YAML::Emitter& out, const Entity& entity);
		static Entity DeserializeEntity(std::unique_ptr<World>& world, const YAML::Node& node);
	public:
		template <typename T = ComponentBase>
		static bool RegisterComponentDataSerializer(const std::function<std::string(ComponentBase*)>& func);
		static void Serialize(std::unique_ptr<World>& world, const std::string& path);
		static bool Deserialize(std::unique_ptr<World>& world, const std::string& path);
	};

	template <typename T>
	bool SerializationManager::RegisterComponentDataSerializer(const std::function<std::string(ComponentBase*)>& func)
	{
		return Get()._ComponentDataSerializers.insert({ typeid(T).hash_code(), func }).second;
	}
}
