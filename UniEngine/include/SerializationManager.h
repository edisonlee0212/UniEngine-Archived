#pragma once
#include "Core.h"

namespace YAML {
	class Node;
	class Emitter;
}

#define EXPORT_PARAM(x, y) (x) << "{" << (y) << "}"
#define IMPORT_PARAM(x, y, temp) (x) >> (temp) >> (y) >> (temp)
namespace UniEngine
{
	std::ostream& operator<<(std::ostream& out, const glm::vec2& v);
	std::ostream& operator<<(std::ostream& out, const glm::vec3& v);
	std::ostream& operator<<(std::ostream& out, const glm::vec4& v);
	std::ostream& operator<<(std::ostream& out, const glm::mat4& v);

	std::istream& operator>>(std::istream& in, glm::vec2& v);
	std::istream& operator>>(std::istream& in, glm::vec3& v);
	std::istream& operator>>(std::istream& in, glm::vec4& v);
	std::istream& operator>>(std::istream& in, glm::mat4& v);

	
	class UNIENGINE_API SerializationManager : public Singleton<SerializationManager>
	{
		std::unordered_map<size_t, std::pair<std::function<std::string(ComponentBase*)>, std::function<void(const std::string&, ComponentBase*)>>> _ComponentDataSerializers;
		static void SerializeEntity(std::unique_ptr<World>& world, YAML::Emitter& out, const Entity& entity);
		static Entity DeserializeEntity(std::unique_ptr<World>& world, const YAML::Node& node, std::map<std::string, std::map<size_t, std::vector<Entity>>>& sharedComponentEntityMap);
	public:
		template <typename T = ComponentBase>
		static bool RegisterComponentDataSerializerDeserializer(const std::pair<std::function<std::string(ComponentBase*)>, std::function<void(const std::string&, ComponentBase*)>>& funcPair);
		static void Serialize(std::unique_ptr<World>& world, const std::string& path);
		static bool Deserialize(std::unique_ptr<World>& world, const std::string& path);
		static void Init();
	};

	template <typename T>
	bool SerializationManager::RegisterComponentDataSerializerDeserializer(const std::pair<std::function<std::string(ComponentBase*)>, std::function<void(const std::string&, ComponentBase*)>>& funcPair)
	{
		return Get()._ComponentDataSerializers.insert({ typeid(T).hash_code(), funcPair }).second;
	}
}
