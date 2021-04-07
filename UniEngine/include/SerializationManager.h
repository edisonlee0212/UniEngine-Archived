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
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v);
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v);
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v);
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::mat4& v);

	
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
		std::unordered_map<size_t, std::pair<std::function<std::string(ComponentDataBase*)>, std::function<void(const std::string&, ComponentDataBase*)>>> m_componentDataSerializers;
		static void SerializeEntity(std::unique_ptr<World>& world, YAML::Emitter& out, const Entity& entity);
		static Entity DeserializeEntity(std::unique_ptr<World>& world, const YAML::Node& node);
	public:
		template <typename T = ComponentDataBase>
		static bool RegisterComponentDataSerializerDeserializer(const std::pair<std::function<std::string(ComponentDataBase*)>, std::function<void(const std::string&, ComponentDataBase*)>>& funcPair);
		static void Serialize(std::unique_ptr<World>& world, const std::string& path);
		static bool Deserialize(std::unique_ptr<World>& world, const std::string& path);
		static void Init();
	};

	template <typename T>
	bool SerializationManager::RegisterComponentDataSerializerDeserializer(const std::pair<std::function<std::string(ComponentDataBase*)>, std::function<void(const std::string&, ComponentDataBase*)>>& funcPair)
	{
		return GetInstance().m_componentDataSerializers.insert({ typeid(T).hash_code(), funcPair }).second;
	}
}
