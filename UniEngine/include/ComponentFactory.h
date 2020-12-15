#pragma once
#include "UniEngineAPI.h"
#include "Singleton.h"
#include "Entity.h"
namespace UniEngine
{
	class ComponentFactory : public Singleton<ComponentFactory>
	{
		std::unordered_map<std::string, const std::function<std::shared_ptr<ComponentBase>()>> _ComponentDataGenerators;
		std::unordered_map<std::string, const std::function<std::shared_ptr<SharedComponentBase>()>> _SharedComponentGenerators;
	public:
		UNIENGINE_API static bool RegisterComponentData(const std::string& id, const std::function<std::shared_ptr<ComponentBase>()>& func);
		UNIENGINE_API static std::shared_ptr<ComponentBase> ProduceComponentData(const std::string& id);
		UNIENGINE_API static bool RegisterSharedComponent(const std::string& id, const std::function<std::shared_ptr<SharedComponentBase>()>& func);
		UNIENGINE_API static std::shared_ptr<SharedComponentBase> ProduceSharedComponent(const std::string& id);
	};

	template <typename T = ComponentBase>
	class UNIENGINE_API ComponentDataRegistration
	{
	public:
		ComponentDataRegistration()
		{
			std::string id = typeid(T).name();
			ComponentFactory::RegisterComponentData(id, []()
				{
					return std::move(std::dynamic_pointer_cast<ComponentBase>(std::make_shared<T>()));
				}
			);
		}
	};

	template <typename T = SharedComponentBase>
	class UNIENGINE_API SharedComponentRegistration
	{
	public:
		SharedComponentRegistration()
		{
			std::string id = typeid(T).name();
			ComponentFactory::RegisterSharedComponent(id, []()
				{
					return std::move(std::dynamic_pointer_cast<SharedComponentBase>(std::make_shared<T>()));
				}
			);
		}
	};
}
