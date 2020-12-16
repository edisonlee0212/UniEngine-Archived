#include "pch.h"
#include "SerializationManager.h"
#include "yaml-cpp/yaml.h"

void UniEngine::SerializationManager::SerializeEntity(std::unique_ptr<World>& world, YAML::Emitter& out, const Entity& entity)
{
	out << YAML::BeginMap;
	out << YAML::Key << "Entity" << YAML::Value << std::to_string(entity.Index);
	out << YAML::Key << "ArchetypeName" << YAML::Value << EntityManager::GetEntityArchetypeName(EntityManager::GetEntityArchetype(entity));
	out << YAML::Key << "Name" << YAML::Value << entity.GetName();
	out << YAML::Key << "Parent" << YAML::Value << EntityManager::GetParent(entity).Index;
#pragma region ComponentData
	out << YAML::Key << "ComponentData" << YAML::Value << YAML::BeginSeq;
	auto& storage = world->_WorldEntityStorage;
	std::vector<ComponentType>& componentTypes =
		storage.EntityComponentStorage[storage.EntityInfos[entity.Index].ArchetypeInfoIndex].ArchetypeInfo->ComponentTypes;
	for (const auto& type : componentTypes)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Name" << YAML::Value << type.Name;
		std::string value;
		const auto it = Get()._ComponentDataSerializers.find(type.TypeID);
		if (it != Get()._ComponentDataSerializers.end())
		{
			ComponentBase* ptr = EntityManager::GetComponentDataPointer(entity, type.TypeID);
			value = it->second.first(ptr);
		}
		out << YAML::Key << "Content" << YAML::Value << value;
		out << YAML::EndMap;
	}
	out << YAML::EndSeq;
#pragma endregion

#pragma region Private Components
	out << YAML::Key << "PrivateComponent" << YAML::Value << YAML::BeginSeq;
	EntityManager::ForEachPrivateComponent(entity, [&](PrivateComponentElement& data)
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Name";
			out << YAML::Value << data.Name;
			data.PrivateComponentData->Serialize(out);
			out << YAML::EndMap;
		}
	);
	out << YAML::EndSeq;
#pragma endregion

#pragma region Shared Components
	out << YAML::Key << "SharedComponent" << YAML::Value << YAML::BeginSeq;
	EntityManager::ForEachSharedComponent(entity, [&](SharedComponentElement data)
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Name";
			out << YAML::Value << data.Name;
			out << YAML::Key << "HashCode" << YAML::Value << data.SharedComponentData->GetHashCode();
			out << YAML::EndMap;
		}
	);
	out << YAML::EndSeq;
#pragma endregion

	out << YAML::EndMap;
}

UniEngine::Entity UniEngine::SerializationManager::DeserializeEntity(std::unique_ptr<World>& world,
	const YAML::Node& node, std::map<std::string, std::map<size_t, std::vector<Entity>>>& sharedComponentEntityMap)
{
	const auto entityName = node["Name"].as<std::string>();
	const auto archetypeName = node["ArchetypeName"].as<std::string>();
	auto componentDatum = node["ComponentData"];
	Entity retVal;

	std::vector<std::shared_ptr<ComponentBase>> ptrs;
	std::vector<ComponentType> types;
	for (const auto& componentData : componentDatum)
	{
		auto name = componentData["Name"].as<std::string>();
		size_t hashCode;
		size_t size;
		auto ptr = ComponentFactory::ProduceComponentData(name, hashCode, size);

		//Deserialize componentData here.
		const auto it = Get()._ComponentDataSerializers.find(hashCode);
		if (it != Get()._ComponentDataSerializers.end())
		{
			it->second.second(componentData["Content"].as<std::string>(), ptr.get());
		}
		ptrs.push_back(ptr);
		types.emplace_back(name, hashCode, size);
	}
	const EntityArchetype archetype = EntityManager::CreateEntityArchetype(archetypeName, types);
	retVal = EntityManager::CreateEntity(archetype, entityName);
	for (int i = 0; i < ptrs.size(); i++)
	{
		EntityManager::SetComponentData(retVal, types[i].TypeID, types[i].Size, ptrs[i].get());
	}

	auto privateComponents = node["PrivateComponent"];
	if(privateComponents)
	{
		for(const auto& privateComponent : privateComponents)
		{
			auto name = privateComponent["Name"].as<std::string>();
			size_t hashCode;
			auto* ptr = dynamic_cast<PrivateComponentBase*>(ComponentFactory::ProduceSerializableObject(
				name, hashCode));
			ptr->Deserialize(privateComponent);
			EntityManager::SetPrivateComponent(retVal, name, hashCode, ptr);
		}
	}

	auto sharedComponents = node["SharedComponent"];
	if (sharedComponents)
	{
		for (const auto& sharedComponent : sharedComponents)
		{
			const auto name = sharedComponent["Name"].as<std::string>();
			const auto componentHashCode = sharedComponents["HashCode"].as<size_t>();
			sharedComponentEntityMap[name][componentHashCode].push_back(retVal);
		}
	}
	return retVal;
}

void UniEngine::SerializationManager::Serialize(std::unique_ptr<World>& world, const std::string& path)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "World";
	out << YAML::Value << "World_Name";
	out << YAML::Key << "Entities";
	out << YAML::Value << YAML::BeginSeq;
	for (const auto& entity : world->_WorldEntityStorage.Entities)
	{
		if (entity.Version == 0) continue;
		SerializeEntity(world, out, entity);
	}
	out << YAML::EndSeq;

	out << YAML::Key << "SharedComponentStorage";
	out << YAML::Value << YAML::BeginSeq;
	for(const auto& sharedComponentCollection : world->_WorldEntityStorage.EntitySharedComponentStorage._SCCollectionsList)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Name";
		out << YAML::Value << sharedComponentCollection->Name;
		out << YAML::Key << "SharedComponents" << YAML::BeginSeq;
		for(const auto& sharedComponent : sharedComponentCollection->_SCList)
		{
			out << YAML::BeginMap;
			out << YAML::Key << "HashCode" << YAML::Value << sharedComponent->GetHashCode();
			sharedComponent->Serialize(out);
			out << YAML::EndMap;
		}
		out << YAML::EndSeq << YAML::EndMap;
	}
	out << YAML::EndSeq;

	out << YAML::EndMap;
	std::ofstream fout(path);
	fout << out.c_str();
	fout.flush();
}

bool UniEngine::SerializationManager::Deserialize(std::unique_ptr<World>& world, const std::string& path)
{
	std::ifstream stream(path);
	std::stringstream stringStream;
	stringStream << stream.rdbuf();
	YAML::Node data = YAML::Load(stringStream.str());
	if (!data["World"])
	{
		return false;
	}
	Debug::Log("Loading world...");
	world->Purge();
	auto entities = data["Entities"];
	if (entities)
	{
		std::unordered_map<unsigned, Entity> entityMap;
		std::vector<std::pair<unsigned, unsigned>> childParentPairs;
		std::map<std::string, std::map<size_t, std::vector<Entity>>> sharedComponentEntityMap;//Class name - ComponentHashCode
		std::map<std::string, std::pair<size_t, std::map<size_t, std::shared_ptr<SharedComponentBase>>>> sharedComponentMap;
		for (const auto& node : entities)
		{
			auto id = node["Entity"].as<unsigned>();
			auto parent = node["Parent"].as<unsigned>();
			
			auto entity = DeserializeEntity(world, node, sharedComponentEntityMap);
			if (entity.IsNull())
			{
				Debug::Error("Error!");
			}
			entityMap.insert({ id, entity });
			if (parent == 0)
				continue;
			childParentPairs.emplace_back(id, parent);
		}
		for (const auto& [fst, snd] : childParentPairs)
		{
			EntityManager::SetParent(entityMap[fst], entityMap[snd]);
		}

		auto sharedComponentStorage = data["SharedComponentsStorage"];
		if(sharedComponentStorage)
		{
			for(const auto& sharedComponentCollection : sharedComponentStorage)
			{
				const auto name = sharedComponentCollection["Name"].as<std::string>();
				const auto sharedComponents = sharedComponentCollection["SharedComponents"];
				if(sharedComponents)
				{
					for(const auto& sharedComponent : sharedComponents)
					{
						const auto hashCode = sharedComponent["HashCode"].as<size_t>();
						size_t id;
						auto* ptr = dynamic_cast<SharedComponentBase*>(ComponentFactory::ProduceSerializableObject(
							name, id));
						ptr->Deserialize(sharedComponent);
						sharedComponentMap[name].first = id;
						sharedComponentMap[name].second[hashCode] = std::shared_ptr<SharedComponentBase>(ptr);
					}
				}
			}
		}
		for(const auto& collection : sharedComponentEntityMap)
		{
			for(const auto& sharedComponents : collection.second)
			{
				for(const auto& entity : sharedComponents.second)
				{
					EntityManager::SetSharedComponent(entity, collection.first, sharedComponentMap[collection.first].first, sharedComponentMap[collection.first].second[sharedComponents.first]);
				}
			}
		}
	}
	return true;
}
