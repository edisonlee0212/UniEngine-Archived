#include "pch.h"
#include "ComponentFactory.h"
#include "Debug.h"
using namespace UniEngine;

bool ComponentFactory::Register(const std::string& id,
	const std::function<std::shared_ptr<ComponentDataBase>(size_t&, size_t&)>& func)
{
	return GetInstance().m_componentDataGenerators.insert({ id, func }).second;
}

std::shared_ptr<ComponentDataBase> ComponentFactory::ProduceComponentData(const std::string& id, size_t& hashCode, size_t& size)
{
	auto& factory = GetInstance();
	const auto it = factory.m_componentDataGenerators.find(id);
	if(it != GetInstance().m_componentDataGenerators.end())
	{
		return it->second(hashCode, size);
	}
	Debug::Error("Component " + id + "is not registered!");
	throw 1;
}

bool ComponentFactory::Register(const std::string& id,
	const std::function<Serializable* (size_t&)>& func)
{
	return GetInstance().m_classComponentGenerators.insert({ id, func }).second;
}

Serializable* ComponentFactory::ProduceSerializableObject(const std::string& id, size_t& hashCode)
{
	const auto it = GetInstance().m_classComponentGenerators.find(id);
	if (it != GetInstance().m_classComponentGenerators.end())
	{
		return it->second(hashCode);
	}
	Debug::Error("Component " + id + "is not registered!");
	throw 1;
}
