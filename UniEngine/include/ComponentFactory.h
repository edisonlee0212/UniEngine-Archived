#pragma once
#include "UniEngineAPI.h"
#include "Singleton.h"
#include "Entity.h"
namespace UniEngine 
{
	class ComponentFactory : public Singleton<ComponentFactory>
	{
		std::unordered_map<std::string, const std::function<std::shared_ptr<ComponentBase>()>> _ComponentDataGenerators;
		std::unordered_map<std::string, const std::function<Serializable*()>> _ClassComponentGenerators;
	public:
		UNIENGINE_API static bool RegisterComponentData(const std::string& id, const std::function<std::shared_ptr<ComponentBase>()>& func);
		UNIENGINE_API static std::shared_ptr<ComponentBase> ProduceComponentData(const std::string& id);
		UNIENGINE_API static bool RegisterComponent(const std::string& id, const std::function<Serializable*()>& func);
		UNIENGINE_API static Serializable* ProduceSharedComponent(const std::string& id);
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

	template <typename T = Serializable>
	class UNIENGINE_API SerializableClassRegistration
	{
	public:
		SerializableClassRegistration()
		{
			std::string id = typeid(T).name();
			ComponentFactory::RegisterComponent(id, []()
				{
					return dynamic_cast<Serializable>(new T());
				}
			);
		}
	};
}
