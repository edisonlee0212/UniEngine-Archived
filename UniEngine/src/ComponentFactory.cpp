#include "pch.h"
#include "ComponentFactory.h"
#include "Debug.h"
using namespace UniEngine;

bool ComponentFactory::Register(const std::string& id,
	const std::function<std::shared_ptr<ComponentBase>(size_t&, size_t&)>& func)
{
	return GetInstance()._ComponentDataGenerators.insert({ id, func }).second;
}

std::shared_ptr<ComponentBase> ComponentFactory::ProduceComponentData(const std::string& id, size_t& hashCode, size_t& size)
{
	auto& factory = GetInstance();
	const auto it = factory._ComponentDataGenerators.find(id);
	if(it != GetInstance()._ComponentDataGenerators.end())
	{
		return it->second(hashCode, size);
	}
	Debug::Error("Component " + id + "is not registered!");
	throw 1;
}

bool ComponentFactory::Register(const std::string& id,
	const std::function<Serializable* (size_t&)>& func)
{
	return GetInstance()._ClassComponentGenerators.insert({ id, func }).second;
}

Serializable* ComponentFactory::ProduceSerializableObject(const std::string& id, size_t& hashCode)
{
	const auto it = GetInstance()._ClassComponentGenerators.find(id);
	if (it != GetInstance()._ClassComponentGenerators.end())
	{
		return it->second(hashCode);
	}
	Debug::Error("Component " + id + "is not registered!");
	throw 1;
}
