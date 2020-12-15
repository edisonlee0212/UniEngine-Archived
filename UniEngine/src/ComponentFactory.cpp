#include "pch.h"
#include "ComponentFactory.h"
#include "Debug.h"
using namespace UniEngine;

bool ComponentFactory::RegisterComponentData(const std::string& id,
	const std::function<std::shared_ptr<ComponentBase>()>& func)
{
	return Get()._ComponentDataGenerators.insert({ id, func }).second;
}

std::shared_ptr<ComponentBase> ComponentFactory::ProduceComponentData(const std::string& id)
{
	const auto it = Get()._ComponentDataGenerators.find(id);
	if(it != Get()._ComponentDataGenerators.end())
	{
		return it->second();
	}
	Debug::Error("Component " + id + "is not registered!");
	throw 1;
}

bool ComponentFactory::RegisterSharedComponent(const std::string& id,
	const std::function<std::shared_ptr<SharedComponentBase>()>& func)
{
	return Get()._SharedComponentGenerators.insert({ id, func }).second;
}

std::shared_ptr<SharedComponentBase> ComponentFactory::ProduceSharedComponent(const std::string& id)
{
	const auto it = Get()._SharedComponentGenerators.find(id);
	if (it != Get()._SharedComponentGenerators.end())
	{
		return it->second();
	}
	Debug::Error("Component " + id + "is not registered!");
	throw 1;
}
