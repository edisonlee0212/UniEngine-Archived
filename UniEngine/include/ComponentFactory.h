#pragma once
#include "UniEngineAPI.h"
#include "Singleton.h"
#include "Entity.h"
namespace UniEngine 
{
	class ComponentFactory : public Singleton<ComponentFactory>
	{
		std::unordered_map<std::string, const std::function<std::shared_ptr<ComponentBase>(size_t&, size_t&)>> _ComponentDataGenerators;
		std::unordered_map<std::string, const std::function<Serializable*()>> _ClassComponentGenerators;
	public:
		UNIENGINE_API bool RegisterComponentData(const std::string& id, const std::function<std::shared_ptr<ComponentBase>(size_t&, size_t&)>& func);
		UNIENGINE_API std::shared_ptr<ComponentBase> ProduceComponentData(const std::string& id, size_t& hashCode, size_t& size);
		UNIENGINE_API bool RegisterComponent(const std::string& id, const std::function<Serializable*()>& func);
		UNIENGINE_API Serializable* ProduceSharedComponent(const std::string& id);
	};
	namespace ComponentFactoryRegistrations {
		template <typename T = ComponentBase>
		class UNIENGINE_API ComponentDataRegistration
		{
		public:
			ComponentDataRegistration(int none)
			{
				std::string id = typeid(T).name();
				ComponentFactory::Get().RegisterComponentData(id, [](size_t& hashCode, size_t& size)
					{
						hashCode = typeid(T).hash_code();
						size = sizeof(T);
						return std::move(std::dynamic_pointer_cast<ComponentBase>(std::make_shared<T>()));
					}
				);
			}
		};

		template <typename T = Serializable>
		class UNIENGINE_API SerializableClassRegistration
		{
		public:
			SerializableClassRegistration(int none)
			{
				std::string id = typeid(T).name();
				ComponentFactory::Get().RegisterComponent(id, []()
					{
						return dynamic_cast<Serializable>(new T());
					}
				);
			}
		};
	}
}
